// This file was automatically generated by the Panda compiler
#ifndef panda$io$MemoryOutputStream_H
#define panda$io$MemoryOutputStream_H
extern panda$core$Class panda$io$MemoryOutputStream_class;
#ifndef CLASS_panda$io$MemoryOutputStream
#define CLASS_panda$io$MemoryOutputStream
struct panda$io$MemoryOutputStream {
    panda$core$Class* cl;
    Bit closed;
    panda$collections$Array$LTpanda$core$UInt8$GT* buffer;
};

#define panda$io$MemoryOutputStream$convert_$Rpanda$core$String_INDEX 1
typedef panda$core$String*(panda$io$MemoryOutputStream$convert_$Rpanda$core$String_TYPE)(panda$io$MemoryOutputStream* self);
#define panda$io$MemoryOutputStream$write_UInt8_INDEX 6
typedef void(panda$io$MemoryOutputStream$write_UInt8_TYPE)(panda$io$MemoryOutputStream* self, UInt8);
#define panda$io$MemoryOutputStream$write_panda$collections$ListView$LTpanda$core$UInt8$GT_Int64_Int64_INDEX 8
typedef void(panda$io$MemoryOutputStream$write_panda$collections$ListView$LTpanda$core$UInt8$GT_Int64_Int64_TYPE)(panda$io$MemoryOutputStream* self, panda$collections$ListView$LTpanda$core$UInt8$GT*, Int64, Int64);
#define panda$io$MemoryOutputStream$reset_INDEX 21
typedef void(panda$io$MemoryOutputStream$reset_TYPE)(panda$io$MemoryOutputStream* self);
#define panda$io$MemoryOutputStream$sendTo_panda$io$OutputStream_INDEX 22
typedef void(panda$io$MemoryOutputStream$sendTo_panda$io$OutputStream_TYPE)(panda$io$MemoryOutputStream* self, panda$io$OutputStream*);
#define panda$io$MemoryOutputStream$$ARR_Int64_$Rpanda$core$UInt8_INDEX 23
typedef UInt8(panda$io$MemoryOutputStream$$ARR_Int64_$Rpanda$core$UInt8_TYPE)(panda$io$MemoryOutputStream* self, Int64);
#define panda$io$MemoryOutputStream$convert_$Rpanda$collections$Array$LTpanda$core$UInt8$GT_INDEX 24
typedef panda$collections$Array$LTpanda$core$UInt8$GT*(panda$io$MemoryOutputStream$convert_$Rpanda$collections$Array$LTpanda$core$UInt8$GT_TYPE)(panda$io$MemoryOutputStream* self);
#define panda$io$MemoryOutputStream$convert_$Rpanda$collections$Array$LTpanda$core$Char$GT_INDEX 25
typedef panda$collections$Array$LTpanda$core$Char$GT*(panda$io$MemoryOutputStream$convert_$Rpanda$collections$Array$LTpanda$core$Char$GT_TYPE)(panda$io$MemoryOutputStream* self);
void panda$io$MemoryOutputStream$init(panda$io$MemoryOutputStream* self);
panda$io$MemoryOutputStream* new_panda$io$MemoryOutputStream$init();
void panda$io$MemoryOutputStream$init_Int64(panda$io$MemoryOutputStream* self, Int64);
panda$io$MemoryOutputStream* new_panda$io$MemoryOutputStream$init_Int64(Int64);
Int64 panda$io$MemoryOutputStream$get_count_$Rpanda$core$Int64(panda$io$MemoryOutputStream* self);
void panda$io$MemoryOutputStream$$classInit_class();
extern Int64 class_panda$io$MemoryOutputStream$DEFAULT_COUNT;
extern Bit class_panda$io$MemoryOutputStream$$classInited;
#endif
#endif