// Special thanks to Nicolas Brailovsky, whose blog
// (http://monoinfinito.wordpress.com/category/programming/c/exceptions/) is the
// only reason I was able to get exception handling working. Much of this code
// was copied from his example.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <unwind.h>
#include <typeinfo>

#define DW_EH_PE_absptr         0x00
#define DW_EH_PE_omit           0xff
#define DW_EH_PE_uleb128        0x01
#define DW_EH_PE_udata2         0x02
#define DW_EH_PE_udata4         0x03
#define DW_EH_PE_udata8         0x04
#define DW_EH_PE_sleb128        0x09
#define DW_EH_PE_sdata2         0x0A
#define DW_EH_PE_sdata4         0x0B
#define DW_EH_PE_sdata8         0x0C
#define DW_EH_PE_signed         0x08
#define DW_EH_PE_pcrel          0x10
#define DW_EH_PE_textrel        0x20
#define DW_EH_PE_datarel        0x30
#define DW_EH_PE_funcrel        0x40
#define DW_EH_PE_aligned        0x50
#define DW_EH_PE_indirect	    0x80

extern "C" {

#include "pandalib.h"

typedef void (*unexpected_handler)(void);
typedef void (*terminate_handler)(void);

/**********************************************/

int readByte(uint8_t** data) {
    uint32_t result = **data;
    (*data)++;
    return result;
}


int readInt32(uint8_t** data) {
    uint32_t result = 0;
    uint8_t* ptr;
    result |= readByte(data);
    result |= readByte(data) << 8;
    result |= readByte(data) << 16;
    result |= readByte(data) << 24;
    return result;
}

int32_t readSLEB128(uint8_t** data) {
    uintptr_t result = 0;
    uintptr_t shift = 0;
    unsigned char byte;
    do {
        byte = readByte(data);
        result |= static_cast<uintptr_t>(byte & 0x7F) << shift;
        shift += 7;
    } 
    while (byte & 0x80);

    if ((byte & 0x40) && (shift < (sizeof(result) << 3)))
        result |= static_cast<uintptr_t>(~0) << shift;

    return static_cast<int>(result);
}

uint32_t readULEB128(uint8_t** data) {
    uintptr_t result = 0;
    uintptr_t shift = 0;
    unsigned char byte;
    do {
        byte = readByte(data);
        result |= static_cast<uintptr_t>(byte & 0x7F) << shift;
        shift += 7;
    } 
    while (byte & 0x80);

    return static_cast<int>(result);
}

struct LSDA_Header {
    /**
     * Read the LSDA table into a struct; advances the lsda pointer
     * as many bytes as read
     */
    LSDA_Header(uint8_t* *lsda) {
        start_encoding = readByte(lsda);
        type_encoding = readByte(lsda);
        type_table_offset = readULEB128(lsda);
    }

    uint8_t start_encoding;
    uint8_t type_encoding;

    // This is the offset, from the end of the header, to the types table
    uint32_t type_table_offset;
};

struct Call_Site_Header {
    // Same as other LSDA constructors
    Call_Site_Header(uint8_t** lsda) {
        encoding = readByte(lsda);
        length = readULEB128(lsda);
    }

    uint8_t encoding;
    uint32_t length;
};

struct Call_Site {
    // Same as other LSDA constructors
    Call_Site(uint8_t** lsda) {
        start = readInt32(lsda);
        len = readInt32(lsda);
        lp = readInt32(lsda);
        action = readByte(lsda);
    }

    Call_Site() { }

    // Note start, len and lp would be void*'s, but they are actually relative
    // addresses: start and lp are relative to the start of the function, len
    // is relative to start
 
    // Offset into function from which we could handle a throw
    uint32_t start;
    
    // Length of the block that might throw
    uint32_t len;
    
    // Landing pad
    uint32_t lp;
    
    // Offset into action table + 1 (0 means no action)
    // Used to run destructors
    int action;

    bool has_landing_pad() const { return lp; }

    /**
     * Returns true if the instruction pointer for this call frame
     * (throw_ip) is in the range of the landing pad for this call
     * site; if true that means the exception was thrown from within
     * this try/catch block
     */
    bool valid_for_throw_ip(uintptr_t func_start, uintptr_t throw_ip) const {
        // Calculate the range of the instruction pointer valid for this
        // landing pad; if this LP can handle the current exception then
        // the IP for this stack frame must be in this range
        uintptr_t try_start = func_start + this->start;
        uintptr_t try_end = func_start + this->start + this->len;
        // Check if this is the correct LP for the current try block
        if (throw_ip < try_start) return false;
        if (throw_ip > try_end) return false;

        // The current exception was thrown from this landing pad
        return true;
    }
};

/**
 * A class to read the language specific data for a function
 */
struct LSDA {
    LSDA_Header header;

    // The types_table_start holds all the types this stack frame
    // could handle (as 32 bit offsets to the pointer locations)
    const uint32_t* types_table_start;

    // With the call site header we can calculate the length of the
    // call site table
    Call_Site_Header cs_header;

    // A pointer to the start of the call site table
    uint8_t* cs_table_start;

    // A pointer to the end of the call site table
    uint8_t* cs_table_end;

    // A pointer to the start of the action table, where an action is
    // defined for each call site
    uint8_t* action_tbl_start;

    LSDA(uint8_t* raw_lsda) :
        // Read LSDA header for the LSDA, advance the ptr
        header(&raw_lsda),

        // Get the start of the types table (it's actually the end of the
        // table, but since the action index will hold a negative index
        // for this table we can say it's the beginning
        types_table_start((uint32_t*) (raw_lsda + header.type_table_offset)),

        // Read the LSDA CS header
        cs_header(&raw_lsda),

        // The call site table starts immediately after the CS header
        cs_table_start(raw_lsda),

        // Calculate where the end of the LSDA CS table is
        cs_table_end(raw_lsda + cs_header.length),

        // Get the start of action tables
        action_tbl_start(cs_table_end) {
        }
   

    Call_Site next_cs_entry;
    uint8_t* next_cs_entry_ptr;

    const Call_Site* next_call_site_entry(bool start=false) {
        if (start) 
            next_cs_entry_ptr = cs_table_start;

        // If we went over the end of the table return NULL
        if (next_cs_entry_ptr >= cs_table_end)
            return NULL;

        // Copy the call site table and advance the cursor by sizeof(Call_Site).
        // We need to copy the struct here because there might be alignment
        // issues otherwise
        next_cs_entry = Call_Site(&next_cs_entry_ptr);

        return &next_cs_entry;
    }


    /**
     * Returns a pointer to the action entry for a call site entry or
     * null if the CS has no action
     */
    const uint8_t* get_action_for_call_site(const Call_Site *cs) const {
        if (cs->action == 0) return NULL;

        const size_t action_offset = cs->action - 1;
        return this->action_tbl_start + action_offset;
    }


    /**
     * An entry in the action table
     */
    struct Action {
        // An index into the types table
        int type_index;

        // Offset for the next action, relative from this byte (this means
        // that the next action will begin exactly at the address of
        // &next_offset - next_offset itself
        int next_offset;

        // A pointer to the raw action, which we need to get the next
        // action:
        //   next_action_offset = raw_action_ptr[1]
        //   next_action_ptr = &raw_action_ptr[1] + next_action_offset
        uint8_t* raw_action_ptr;

    } current_action;


    /**
     * Gets the first action for a specific call site
     */
    const Action* get_first_action_for_cs(const Call_Site *cs) {
        // The call site may have no associated action (in that case
        // it should be a cleanup)
        if (cs->action == 0) return NULL;

        // The action in the CS is 1 based: 0 means no action and
        // 1 is the element 0 on the action table
        const size_t action_offset = cs->action - 1;
        uint8_t* action_raw = this->action_tbl_start + action_offset;

        current_action.type_index = action_raw[0];
        uint8_t* ptr = action_raw + 1;
        current_action.next_offset = readSLEB128(&ptr);
        current_action.raw_action_ptr = &action_raw[0];
        return &current_action;
    }

    /**
     * Gets the next action, if any, for a CS (after calling
     * get_first_action_for_cs)
     */
    const Action* get_next_action() {
        // If the current_action is the last one then the
        // offset for the next one will be 0
        if (current_action.next_offset == 0) return NULL;

        // To move to the next action we must use raw_action_ptr + 1
        // because the offset is from the next_offset place itself and
        // not from the start of the struct:
        uint8_t* action_raw = current_action.raw_action_ptr + 1 +
                                        current_action.next_offset;

        current_action.type_index = action_raw[0];
        uint8_t* ptr = action_raw + 1;
        current_action.next_offset = readSLEB128(&ptr);
        current_action.raw_action_ptr = &action_raw[0];

        return &current_action;
    }

    /**
     * Returns the type from the types table defined for an action
     */
    Class* get_type_for(const Action* action) const {
        // The index starts at the end of the types table
        int idx = -1 * action->type_index;
        // pointer to the entry in the types table
        const void* entry = &types_table_start[idx];
        // the actual pointer to the type
        void *value;
        if ((header.type_encoding & DW_EH_PE_udata4) == DW_EH_PE_udata4)
            value = (void*) (uintptr_t) *((uint32_t*) entry);
        else if ((header.type_encoding & DW_EH_PE_sdata4) == DW_EH_PE_sdata4)
            value = (void*) (uintptr_t) *((int32_t*) entry);
        else {
            // FIXME handle all encodings
            printf("unsupported type_encoding!\n"); 
        }
        // at this point value is now the raw entry from the types table,
        // without adjusting for pcrel or indirect, so let's fix that
        if (header.type_encoding & DW_EH_PE_pcrel)
            value = (void*) (((uintptr_t) value) + (uintptr_t) entry);
        if ((header.type_encoding & DW_EH_PE_indirect) == DW_EH_PE_indirect)
            value = *((Class**) value);
        return (Class*) value;
    }
};


/**********************************************/


bool can_handle(Error* thrown, Class* catchType) {
    return panda$core$Panda$instanceOf((Object*) thrown, catchType, false);
}

_Unwind_Reason_Code run_landing_pad(_Unwind_Exception* unwind_exception,
         _Unwind_Context* context, int exception_type_idx,
         uintptr_t lp_address) {
    int r0 = __builtin_eh_return_data_regno(0);
    int r1 = __builtin_eh_return_data_regno(1);

    _Unwind_SetGR(context, r0, (uintptr_t) (unwind_exception));
    _Unwind_SetGR(context, r1, (uintptr_t) (exception_type_idx));
    _Unwind_SetIP(context, lp_address);
    return _URC_INSTALL_CONTEXT;
}

// The personality function is called automatically by the exception unwinder,
// once per stack frame which contains catch information. Its job is to scan
// through the catch information and determine whether we are supposed to jump
// into one of those catches, or continue unwinding the stack.
_Unwind_Reason_Code pandaPersonality(int version, _Unwind_Action actions,
        uint64_t exceptionClass, _Unwind_Exception* unwind_exception,
        _Unwind_Context* context) {
    // Calculate what the instruction pointer was just before the
    // exception was thrown for this stack frame
    uintptr_t throw_ip = _Unwind_GetIP(context) - 1;

    // Get a ptr to the start of the function for this stack frame;
    // this is needed because a lot of the addresses in the LSDA are
    // actually offsets from func_start
    uintptr_t func_start = _Unwind_GetRegionStart(context);

    // Get a pointer to the raw memory address of the LSDA
    uint8_t* raw_lsda = (uint8_t*) _Unwind_GetLanguageSpecificData(context);

    // Create an object to hide some part of the LSDA processing
    LSDA lsda(raw_lsda);

    // Go through each call site in this stack frame to check whether
    // the current exception can be handled here
    for(const Call_Site *cs = lsda.next_call_site_entry(true);
            cs != NULL;
            cs = lsda.next_call_site_entry()) {
        // If there's no landing pad we can't handle this exception
        if (!cs->has_landing_pad()) continue;

        // Calculate the range of the instruction pointer valid for this
        // landing pad; if this LP can handle the current exception then
        // the IP for this stack frame must be in this range
        if (!cs->valid_for_throw_ip(func_start, throw_ip)) continue;

        // Iterate all the actions for this call site
        for (const LSDA::Action* action = lsda.get_first_action_for_cs(cs);
                action != NULL;
                action = lsda.get_next_action()) {
            if (action->type_index == 0) {
                // If there is an action entry but it doesn't point to any
                // type, it means this is actually a cleanup block and we
                // should run it anyway
                //
                // Of course the cleanup should only run on the cleanup phase
                if (actions & _UA_CLEANUP_PHASE) {
                    return run_landing_pad(unwind_exception, context,
                                    action->type_index, func_start + cs->lp);
                }
            } 
            else {
                // Get the type this action can handle
                Class* catch_type = lsda.get_type_for(action);

                Error* thrown = ((_nativeException*) unwind_exception)->pandaException;
                if (can_handle(thrown, catch_type)) {
                    // If we are on search phase, tell _Unwind_ we can handle this one
                    if (actions & _UA_SEARCH_PHASE) return _URC_HANDLER_FOUND;

                    // If we are not on search phase then we are on _UA_CLEANUP_PHASE
                    // and we need to install the context
                    return run_landing_pad(unwind_exception, context,
                                    action->type_index, func_start + cs->lp);
                }
            }
        }
    }
    return _URC_CONTINUE_UNWIND;
}

Error* pandaCatch(_nativeException* ex) {
    return ex->pandaException;
}

}
