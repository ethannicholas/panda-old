#include "pandalib.h"
#include "unicode/utf.h"
#include "unicode/uregex.h"
#include "dirent.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <pthread.h>
#define UNW_LOCAL_ONLY
#include "libunwind.h"
#include "unwind.h"
#include "math.h"

#ifndef GC

#define GC_MALLOC_ATOMIC MALLOC
void GC_INIT() { }

void* malloc_zero(size_t s) {
    return calloc(s, 1);
}

#endif

void* malloc_atomic(size_t size) {
    void* result = GC_MALLOC_ATOMIC(size);
    memset(result, 0, size);
    return result;
}

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

#define UNUSED(x) (void)x

/***** Basic system functions *****/

static String$Array* arg = NULL;

static Bit inited = 0;

static String* executablePath = NULL;

static pthread_mutex_t threadLock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t classLock;

static int preventsExitThreads = 0;
static pthread_cond_t preventsExitThreadsVar = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t preventsExitThreadsMutex = PTHREAD_MUTEX_INITIALIZER;

static int threadLocalCount = 0;

static pthread_key_t currentThreadKey;

static Bit debugAllocations = 0;

Int32 panda$core$Object$hash(Object* object) {
    return (Int32) ((uintptr_t) object); // this will truncate the pointer on
                                         // 64-bit systems, but that's ok
}

// FIXME: add UTF-8 support
char* pandaGetString(String* s) {
    int length = s->chars->$length;
    char* result = (char*) MALLOC(length + 1);
    Char* chars = s->chars->contents;
    int i;
    for (i = 0; i < length; i++) {
        // FIXME: just truncating the characters for now
        result[i] = chars[i] & 0xff;
    }
    result[length] = '\0';
    return result;
}

void* pandaAlloc(Int32 size, Bit containsPointers) {
    if (!inited) {
        pandaFatalError("pandaInit has not been called");
    }
    void* result = containsPointers ? MALLOC(size) : MALLOC_ATOMIC(size);
    if (result == 0)
        pandaFatalError("Malloc failed");
    return result;
}


void pandaInit() {
    if (!inited) {
        GC_INIT();
        pthread_key_create(&currentThreadKey, NULL);
        pthread_mutexattr_t a;
        pthread_mutexattr_init(&a);
        pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&classLock, &a);
        panda$threads$Thread$$classInit();
        inited = TRUE;
    }
}

void pandaMain(String$Array* arg);

void pandaStart() {
    panda$threads$Thread* main = pandaNew(panda$threads$Thread);
    panda$threads$Thread$init(main);
    panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT* threadLocals = pandaNew(panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT);
    panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT$init(threadLocals);
    main->threadLocals = threadLocals;
    pthread_setspecific(currentThreadKey, main);
    // run the actual program
    pandaMain(arg);
}

int main(int argc, char** argv) {
    pandaInit();
    // convert args to panda strings
    executablePath = pandaNewString(argv[0], strlen(argv[0]));
    argc--;
    argv++;
    arg = (String$Array*) pandaNewPrimitiveArrayWithLength(&panda$collections$PrimitiveArray$LTpanda$core$String$GT_class, 
            argc, sizeof(String*), true);
    String** contents = (String**) arg->contents;
    int i;
    for (i = 0; i < argc; i++)
        contents[i] = pandaNewString(argv[i], -1);
    pandaStart();

    // ensure all threads have exited
    pthread_mutex_lock(&preventsExitThreadsMutex);
    for (;;) {
        if (preventsExitThreads == 0)
            break;
        pthread_cond_wait(&preventsExitThreadsVar, &preventsExitThreadsMutex);
    }
    pthread_mutex_unlock(&threadLock);
    
    return 0;
}

typedef void (*finalizer)(Object*);
typedef void *(*threadRun)(void*);

#ifdef GC
static void runFinalizer(Object* o, finalizer f) {
    f(o);
    o->cl = NULL;
}
#endif

void* pandaGetInterfaceMethod(panda$core$Object* o, panda$core$Class* intf, 
        int index) {
    itable* it = o->cl->itables;
    while (it->cl != intf)
        it = it->next;
    return it->methods[index];
}

// Allocates a new Panda object given its class and size in bytes. In addition
// to the actual allocation of the memory, pandaNew will set the object's
// class_ptr and register its finalizer (if any). All of the object's bytes
// other than class_ptr will be zeroed. The constructor is not called.
// class_ptr - the Panda Class object
// size - the number of bytes to allocate
Object* _pandaNew(Class* class_ptr, Int32 size) {
    Object* result = (Object*) pandaAlloc(size, class_ptr->containsPointers);
    result->cl = class_ptr;
    if (debugAllocations)
        printf("%s\n", pandaGetString(class_ptr->name));
#ifdef GC
    if (class_ptr->overridesFinalize) {
        GC_finalization_proc oldFinalizer;
        GC_PTR oldCD;
        void (*finalize)() = (void (*)()) *(&class_ptr->vtable + 
                panda$core$Object$finalize_INDEX);
        GC_register_finalizer(result, 
                (GC_finalization_proc) runFinalizer, 
                finalize, 
                &oldFinalizer, 
                &oldCD);
    }
#endif
    return result;
}

// Creates a Panda String from a UTF-8 character sequence.
// chars - the UTF-8 bytes of the text (does not need to be null-terminated)
// byteLength - the length of chars
String* pandaNewString(const char* chars, int byteLength) {
    if (byteLength == -1)
        byteLength = strlen(chars);
    Int32 length = byteLength;
    panda$collections$ImmutablePrimitiveArray$LTpanda$core$Char$GT* data = 
            (panda$collections$ImmutablePrimitiveArray$LTpanda$core$Char$GT*) pandaNewPrimitiveArrayWithLength(
            &panda$collections$ImmutablePrimitiveArray$LTpanda$core$Char$GT_class, 
            length, sizeof(Char), false);
    int i;
    for (i = 0; i < byteLength; i++)
        data->contents[i] = chars[i];
    String* result = pandaNew(panda$core$String);
    result->chars = data;
    return result;
}

// Creates a new Panda Array object. All cells of the array will be zeroed.
// class_ptr - the specific Array class object
// length - the initial length of the array
// elementSize - the size of each element
// elementsArePointers - true if the array elements are pointers (if not,
//         the garbage collector doesn't need to worry about them)
Array* pandaNewPrimitiveArrayWithLength(Class* class_ptr, Int32 length, 
        Int32 elementSize, Bit elementsArePointers) {
    if ((elementSize < 0) || (length < 0))
       pandaFatalError("creating array with negative size");
    Array* result = (Array*) _pandaNew(class_ptr, sizeof(Array));
    result->$length = length;
    result->$maxLength = length;
    result->contents = pandaAlloc(length * elementSize, elementsArePointers);
    return result;
}

// Creates a new Panda Array copied from a subrange of an existing array.
// class_ptr - the specific Array class to create
// array - the array to copy from
// elementSize - size of each element
// elementsArePointers - true if the array elements are pointers (if not,
//         the garbage collector doesn't need to worry about them)
Array* pandaNewPrimitiveArrayCopy(Class* class_ptr, Array* array, 
            Int32 elementSize, Bit elementsArePointers) {
    if (elementSize < 0)
       pandaFatalError("creating array with negative size");
    Array* result = (Array*) _pandaNew(class_ptr, sizeof(Array));
    result->$length = array->$length;
    result->$maxLength = array->$length;
    int size = result->$maxLength * elementSize;
    result->contents = pandaAlloc(size, elementsArePointers);
    memcpy(result->contents, ((Int8*) array->contents), size);
    return result;
}

// Creates a new Panda Array with the specified elements.
// class_ptr - the specific Array class to create
// length - the number of elements being passed in
// elementSize - size of each element
// elementsArePointers - true if the array elements are pointers (if not,
//         the garbage collector doesn't need to worry about them)
Array* pandaNewPrimitiveArrayWithValues(Class* class_ptr, Int32 length, 
        Int32 elementType, ...) {
    if (length < 0)
       pandaFatalError("creating array with negative size");
    Array* result;
    va_list args;
    va_start(args, elementType);
    unsigned char* target;
    int i;
    #define ARRAY_INT8   0
    #define ARRAY_INT16  1
    #define ARRAY_INT32  2
    #define ARRAY_INT64  3
    #define ARRAY_REAL32 4
    #define ARRAY_REAL64 5
    #define ARRAY_PTR    6
    switch (elementType) {
        case ARRAY_INT8: 
            result = pandaNewPrimitiveArrayWithLength(class_ptr, length, sizeof(Int8), 
                    false);
            target = (unsigned char*) result->contents;
            for (i = 0; i < length; i++) {
                Int8 value = (Int8) va_arg(args, Int32);
                memcpy(target, &value, sizeof(Int8));
                target += sizeof(Int8);
            }
            break;
        
        case ARRAY_INT16: 
            result = pandaNewPrimitiveArrayWithLength(class_ptr, length, sizeof(Int16), 
                    false);
            target = (unsigned char*) result->contents;
            for (i = 0; i < length; i++) {
                Int16 value = (Int16) va_arg(args, Int32);
                memcpy(target, &value, sizeof(Int16));
                target += sizeof(Int16);
            }
            break;

        case ARRAY_INT32: 
            result = pandaNewPrimitiveArrayWithLength(class_ptr, length, sizeof(Int32), 
                    false);
            target = (unsigned char*) result->contents;
            for (i = 0; i < length; i++) {
                Int32 value = va_arg(args, Int32);
                memcpy(target, &value, sizeof(Int32));
                target += sizeof(Int32);
            }
            break;

        case ARRAY_INT64:
            result = pandaNewPrimitiveArrayWithLength(class_ptr, length, sizeof(Int64), 
                    false);
            target = (unsigned char*) result->contents;
            for (i = 0; i < length; i++) {
                Int64 value = va_arg(args, Int64);
                memcpy(target, &value, sizeof(Int64));
                target += sizeof(Int64);
            }
            break;
            
        case ARRAY_REAL32: 
            result = pandaNewPrimitiveArrayWithLength(class_ptr, length, sizeof(Real32), 
                    false);
            target = (unsigned char*) result->contents;
            for (i = 0; i < length; i++) {
                Real32 value = (Real32) va_arg(args, Real64);
                memcpy(target, &value, sizeof(Real32));
                target += sizeof(Real32);
            }
            break;

        case ARRAY_REAL64:
            result = pandaNewPrimitiveArrayWithLength(class_ptr, length, sizeof(Real64), 
                    false);
            target = (unsigned char*) result->contents;
            for (i = 0; i < length; i++) {
                Real64 value = va_arg(args, Real64);
                memcpy(target, &value, sizeof(Real64));
                target += sizeof(Real64);
            }
            break;
        
        case ARRAY_PTR:
            result = pandaNewPrimitiveArrayWithLength(class_ptr, length, sizeof(void*), 
                    true);
            target = (unsigned char*) result->contents;
            for (i = 0; i < length; i++) {
                void* value = va_arg(args, void*);
                memcpy(target, &value, sizeof(void*));
                target += sizeof(void*);
            }
            break;

        default:
            fprintf(stderr, "Unsupported element type: %d\n", elementType);
            __builtin_trap();
    }
    va_end(args);
    return result;
    #undef ARRAY_INT8  
    #undef ARRAY_INT16 
    #undef ARRAY_INT32 
    #undef ARRAY_INT64 
    #undef ARRAY_REAL32
    #undef ARRAY_REAL64
    #undef ARRAY_PTR   
}

// Changes the length of an array.
// array - the array being modified
// elementSize - size of each element
// elementsArePointers - true if the array elements are pointers (if not,
//         the garbage collector doesn't need to worry about them)
// newLength - the new length
void panda$collections$PrimitiveArray$setLength(
        panda$core$Object* arrayObject, Int32 elementSize, 
        Bit elementsArePointers, Int32 newLength) {
    Array* array = (Array*) arrayObject;
    int oldLength = array->$length;
    array->$length = newLength;
    Int32 newMax = array->$maxLength;
    if (newLength > newMax) {
        newMax = MAX(newMax, 2);
        while (newLength > newMax)
            newMax *= 2;
        void* newContents = pandaAlloc(newMax * elementSize, elementsArePointers);
        memcpy(newContents, array->contents, oldLength * elementSize);
        FREE(array->contents);
        array->contents = newContents;
        array->$length = newLength;
        array->$maxLength = newMax;
    }
}

void panda$collections$PrimitiveArray$pandaSetArrayLength(
        panda$core$Object* arrayObject, Int32 elementSize, 
        Bit elementsArePointers, Int32 newLength) {
    panda$collections$PrimitiveArray$setLength(arrayObject, 
            elementSize, elementsArePointers, newLength);
}
// Called by the exception handler when we have finished dispatching an 
// exception
// reason - the _Unwind_Reason_Code explaining why this is being called
// e - the _nativeException object to free
void pandaCleanupException(_Unwind_Reason_Code reason, _nativeException* e) {
    // probably doesn't matter, but might as well explicitly free it
    UNUSED(reason);
    FREE(e);
}

// Throws 

void pandaUncaughtException(Error* e) {
    panda$core$Object$convert_TYPE* cnvString = 
            (panda$core$Object$convert_TYPE*) 
                *(&e->cl->vtable + 
                panda$core$Object$convert_INDEX);
    String* stackTrace = cnvString((panda$core$Object*) e);
    printf("%s", pandaGetString(stackTrace));
    __builtin_trap();
}

void pandaThrow(Error* e) {
    _nativeException* nativeException = MALLOC(sizeof(_nativeException));
    nativeException->exception_class = EXCEPTION_CLASS;
    nativeException->pandaException = e;
    _Unwind_Reason_Code result = _Unwind_RaiseException(
            (struct _Unwind_Exception*) nativeException);
    if (result == _URC_END_OF_STACK)
        pandaUncaughtException(e);
}

// note that this only works for exceptions which do not define any additional
// fields beyond those present in Error
void pandaCreateAndThrow(panda$core$Class* exception, const char* message) {
    panda$core$Error* result = (panda$core$Error*)
            _pandaNew(exception, sizeof(panda$core$Error));
    result->stack = panda$core$Error$getStackTrace((panda$core$Error*) result);
    result->message = pandaNewString(message, strlen(message));
    pandaThrow((Error*) result);
}

void pandaCheckBounds(panda$collections$PrimitiveArray* array, Int32 index) {
    if ((index >= array->$length) || (index < 0)) {
        __builtin_trap();
        char buffer[100];
        sprintf(buffer, "Array index out of bounds: requested element %d, array length is %d", 
                index, array->$length);
        pandaCreateAndThrow(&panda$collections$IndexOutOfBoundsError_class, 
                buffer);
    }
}

void pandaCheckOverflow(Bit flag) {
    if (flag) {
        pandaCreateAndThrow(&panda$core$OverflowError_class, 
                "integer overflow");
    }
}

panda$core$Object* panda$core$Object$copy(panda$core$Object* src) {
    return src;
}


// Checks to see if a class is the given type
// srcClass - the class being tested
// testClass - the class we are comparing against
Bit instanceOf(Class* srcClass, Class* testClass) {
    if (srcClass == testClass)
        return TRUE;
    Class* super = srcClass->superclass;
    if (super == srcClass)
        printf("error: %s\n", pandaGetString(srcClass->name));
    if (super != NULL && instanceOf(super, testClass))
        return TRUE;
    struct itable* it = srcClass->itables;
    while (it != NULL) {
        if (it->cl != srcClass) {
            if (instanceOf(it->cl, testClass))
                return TRUE;
        }
        it = it->next;
    }
    return FALSE;
}

void panda$core$Panda$debugAllocations() {
    debugAllocations = 1;
}

Bit panda$core$Panda$instanceOf(Object* object, Class* class_ptr, Bit nullable) {
    if (object == NULL)
        return nullable;
    return instanceOf(object->cl, class_ptr);
}

Int64 panda$core$Panda$currentTime() {
    struct timeval t;
    if (gettimeofday(&t, NULL) == -1)
      abort();
    return ((Int64) t.tv_sec) * 1000  +  ((Int64) t.tv_usec) / 1000;
    
}

void panda$threads$Thread$sleep(Int32 millis) {
    usleep(millis * 1000);
}

panda$core$OperatingSystemInfo* panda$core$System$operatingSystem() {
    panda$core$OperatingSystemType$$classInit();
    panda$core$OperatingSystemType* type;
#ifdef _WIN32
    type = class_panda$core$OperatingSystemType$WINDOWS;
#elif __APPLE__    
    type = class_panda$core$OperatingSystemType$MACOSX;
#elif __linux
    type = class_panda$core$OperatingSystemType$LINUX;
#else
    type = class_panda$core$OperatingSystemType$OTHER_UNIX;
#endif
    panda$core$OperatingSystemInfo* result = 
            pandaNew(panda$core$OperatingSystemInfo);
    result->type = type;
    return result;
}

void panda$core$System$execStream(
        String* program, String* dir, void* inHandleArg, void* outHandleArg, 
        panda$collections$ListView$LTpanda$core$String$GT* pandaArgs) {
    FILE* inHandle = (FILE*) inHandleArg;
    FILE* outHandle = (FILE*) outHandleArg;
    char* path = pandaGetString(program);
    panda$collections$CollectionView$LTpanda$core$String$GT$length_TYPE* length =
            pandaGetInterfaceMethod((panda$core$Object*) pandaArgs, 
                    &panda$collections$CollectionView$LTpanda$core$String$GT_class, 
                    panda$collections$CollectionView$LTpanda$core$String$GT$length_INDEX);
    panda$collections$ListView$LTpanda$core$String$GT$$ARR_TYPE* subscript =
            pandaGetInterfaceMethod((panda$core$Object*) pandaArgs, 
                    &panda$collections$ListView$LTpanda$core$String$GT_class, 
                    panda$collections$ListView$LTpanda$core$String$GT$$ARR_INDEX);
    int argLength = length((panda$collections$CollectionView$LTpanda$core$String$GT*) pandaArgs);
    char* args[argLength + 2];
    args[0] = path;
    int i;
    for (i = 0; i < argLength; i++)
        args[i + 1] = pandaGetString(subscript(pandaArgs, i));
    args[argLength + 1] = NULL;
    pid_t pid = fork();
    if (!pid) {
        if (inHandle != NULL)
            dup2(fileno(inHandle), fileno(stdin));
        dup2(fileno(outHandle), fileno(stdout));
        if (chdir(pandaGetString(dir))) {
            // FIXME: throw exception
            printf("error: could not chdir() to '%s'\n", pandaGetString(dir));
        }
        else {
            execv(path, args);
            fclose(inHandle);
            fclose(outHandle);
        }
    }
    else {
        int status;
        waitpid(pid, &status, 0);
    }
}

void panda$core$System$exec_File_File_ListView$LTString$GT(
        panda$io$File* program, 
        panda$io$File* dir, 
        panda$collections$ListView$LTpanda$core$String$GT* pandaArgs) {
    panda$core$System$execStream(program->path, dir->path, NULL, stdout, 
                pandaArgs);
}

String* panda$core$Environment$pandaGetEnv(String* key) {
    char* result = getenv(pandaGetString(key));
    if (result)
        return pandaNewString(result, strlen(result));
    else
        return NULL;
}

void panda$core$System$exit_Int32(Int32 exitCode) {
    exit(exitCode);
}

void pandaFatalError(const char* msg) {
    fprintf(stdout, "%s\n", msg);
    fflush(stdout);
    __builtin_trap();
}

panda$collections$ImmutablePrimitiveArray$LTpanda$core$StackTraceEntry$GT* panda$core$Error$getStackTrace(
        panda$core$Error* self) {
    (void) self;
    panda$collections$ImmutablePrimitiveArray$LTpanda$core$StackTraceEntry$GT* result = 
            (panda$collections$ImmutablePrimitiveArray$LTpanda$core$StackTraceEntry$GT*) 
            pandaNewPrimitiveArrayWithLength(&panda$collections$ImmutablePrimitiveArray$LTpanda$core$StackTraceEntry$GT_class, 
                    0, sizeof(panda$core$StackTraceEntry*), true);

    unw_cursor_t    cursor;
    unw_context_t   context;

    unw_getcontext(&context);
    unw_init_local(&cursor, &context);
    // skip the first entry, as it's always going to be Error.new
    unw_step(&cursor); 
    Bit done = FALSE;
    while (!done && unw_step(&cursor) > 0) {
        panda$core$StackTraceEntry* entry = 
                pandaNew(panda$core$StackTraceEntry);
        unw_word_t offset;
        unw_word_t pc;
        char fname[255];
        unw_get_reg(&cursor, UNW_REG_IP, &pc);
        fname[0] = '\0';
        (void) unw_get_proc_name(&cursor, fname, sizeof(fname), &offset);
        void* start = (void*) (pc - offset);
        if (start == pandaMain) {
            entry->methodName = pandaNewString("main", 4);
            done = TRUE;
        }
        else
            entry->methodName = pandaNewString(fname, strlen(fname));
        entry->className = pandaNewString("<unknown>", 9);
        int index = result->$length;
        panda$collections$PrimitiveArray$setLength((Object*) result, 
                sizeof(panda$core$StackTraceEntry*), true, index + 1);
        result->contents[index] = entry;
    }
    return result;
}

/***** Simple file I/O *****/

void* panda$io$FileInputStream$open(String* s, Bit read, Bit write) {
    char* name = pandaGetString(s);
    const char* mode;
    if (read && write)
        mode = "r+";
    else if (write)
        mode = "w";
    else
        mode = "r";
    FILE* result = fopen((char *) name, mode);
    if (result == NULL) {
        panda$io$FileNotFoundException* result = 
                pandaNew(panda$io$FileNotFoundException);
        result->stack = panda$core$Error$getStackTrace((panda$core$Error*) result);
        result->message = s;
        pandaThrow((Error*) result);
    }
    return (void*) result;
}

void* panda$io$FileOutputStream$open(
        String* s, Bit read, Bit write) {
    return panda$io$FileInputStream$open(
            s, read, write);
}

Int32 panda$io$FileInputStream$close_$NativePointer_$RInt32(void* handle) {
    return fclose((FILE*) handle);
}

Int32 panda$io$FileOutputStream$close_$NativePointer_$RInt32(void* handle) {
    return fclose((FILE*) handle);
}

void* panda$io$Console$stdIn() {
    return (void*) stdin;
}

void* panda$io$Console$stdOut() {
    return (void*) stdout;
}

short panda$io$FileInputStream$read_$NativePointer_$RInt16(void* handle) {
    unsigned char b;
    if (fread(&b, 1, 1, (FILE*) handle) == 1)
        return b;
    else
        return -1;
}

panda$core$Int32Wrapper* panda$io$FileInputStream$read_ListWriter$LTInt8$GT_Int32_$RInt32$Z(
        panda$io$FileInputStream* self, 
        panda$collections$ListWriter$LTpanda$core$Int8$GT* bytes, 
        Int32 max) {
    panda$collections$CollectionWriter$LTpanda$core$Int8$GT$add_TYPE* add =
            pandaGetInterfaceMethod((panda$core$Object*) bytes, 
                    &panda$collections$CollectionWriter$LTpanda$core$Int8$GT_class, 
                    panda$collections$CollectionWriter$LTpanda$core$Int8$GT$add_INDEX);
    Int8 data[max];
    // FIXME check for errors
    int count = fread(data, 1, max, (FILE*) self->nativeFile);
    if (count <= 0)
        return NULL;
    for (int i = 0; i < count; i++) {
        add((panda$collections$CollectionWriter$LTpanda$core$Int8$GT*) bytes, 
                data[i]);
    }
    panda$core$Int32Wrapper* result = pandaNew(panda$core$Int32Wrapper);
    result->value = count;
    return result;
}

panda$core$Int32Wrapper* panda$io$FileInputStream$read_ListWriter$LTUInt8$GT_Int32_$RInt32$Z(
        panda$io$FileInputStream* self, 
        panda$collections$ListWriter$LTpanda$core$UInt8$GT* bytes,
        Int32 max) {
    panda$collections$CollectionWriter$LTpanda$core$UInt8$GT$add_TYPE* add =
            pandaGetInterfaceMethod((panda$core$Object*) bytes, 
                    &panda$collections$CollectionWriter$LTpanda$core$UInt8$GT_class, 
                    panda$collections$CollectionWriter$LTpanda$core$UInt8$GT$add_INDEX);
    UInt8 data[max];
    // FIXME check for errors
    int count = fread(data, 1, max, (FILE*) self->nativeFile);
    if (count <= 0)
        return NULL;
    for (int i = 0; i < count; i++) {
        add((panda$collections$CollectionWriter$LTpanda$core$UInt8$GT*) bytes, 
                data[i]);
    }
    panda$core$Int32Wrapper* result = pandaNew(panda$core$Int32Wrapper);
    result->value = count;
    return result;
}

panda$core$Int32Wrapper* panda$io$FileInputStream$read_ListWriter$LTChar$GT_Int32_$RInt32$Z(
        panda$io$FileInputStream* self, 
        panda$collections$ListWriter$LTpanda$core$Char$GT* chars, 
        Int32 max) {
    panda$collections$CollectionWriter$LTpanda$core$Char$GT$add_TYPE* add =
            pandaGetInterfaceMethod((panda$core$Object*) chars, 
                    &panda$collections$CollectionWriter$LTpanda$core$Char$GT_class, 
                    panda$collections$CollectionWriter$LTpanda$core$Char$GT$add_INDEX);
    Char data[max];
    // FIXME check for errors
    int count = fread(data, 1, max, (FILE*) self->nativeFile);
    if (count <= 0)
        return NULL;
    for (int i = 0; i < count; i++) {
        add((panda$collections$CollectionWriter$LTpanda$core$Char$GT*) chars, 
                data[i]);
    }
    panda$core$Int32Wrapper* result = pandaNew(panda$core$Int32Wrapper);
    result->value = count;
    return result;
}

void panda$io$FileOutputStream$writeInt8(void* handle, Int8 b) {
    // FIXME check for errors
    fwrite(&b, 1, 1, (FILE*) handle);
}

void panda$collections$Array$LTpanda$core$Int8$GT$$ARR();

void panda$io$FileOutputStream$writeInt8Array(void* handle, 
        panda$collections$ListView$LTpanda$core$Int8$GT* b, Int32 offset, 
        Int32 length) {
    panda$collections$ListView$LTpanda$core$Int8$GT$$ARR_TYPE* subscript =
            pandaGetInterfaceMethod((panda$core$Object*) b, 
                    &panda$collections$ListView$LTpanda$core$Int8$GT_class, 
                    panda$collections$ListView$LTpanda$core$Int8$GT$$ARR_INDEX);
    const Int32 BUFFER_SIZE = 8192;
    Int8 data[BUFFER_SIZE];
    while (length > 0) {
        int currentLength = MIN(length, BUFFER_SIZE);
        for (int i = 0; i < currentLength; i++)
            data[i] = subscript(b, i + offset);
        // FIXME check for errors
        fwrite(data, currentLength, 1, (FILE*) handle);
        length -= currentLength;
        offset += currentLength;
    }
}

panda$collections$ListView$LTpanda$io$File$GT* panda$io$File$list_$RListView$LTFile$GT(File* file) {
    const size_t MAX_LENGTH = PATH_MAX;
    char buffer[MAX_LENGTH];
    char* path = pandaGetString(file->path);
    panda$collections$Array$LTpanda$io$File$GT* result;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL) {
        result = pandaNew(panda$collections$Array$LTpanda$io$File$GT);
        panda$collections$Array$LTpanda$io$File$GT$init(result);
        panda$collections$Array$LTpanda$io$File$GT$add_TYPE* add =
                (panda$collections$Array$LTpanda$io$File$GT$add_TYPE*) 
                    *(&result->cl->vtable + 
                    panda$collections$Array$LTpanda$io$File$GT$add_INDEX);    
        while ((ent = readdir(dir)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            int namelength = strlen(ent->d_name);
            if (strlen(path) + 1 + namelength > MAX_LENGTH)
                pandaFatalError("path name too long");
            namelength = sprintf(buffer, "%s/%s", path, ent->d_name);
            String* filename = pandaNewString(buffer, namelength);
            File* file = pandaNew(panda$io$File);
            file->path = filename;
            add(result, file);
        }
        closedir(dir);
    } 
    else
        result = NULL;
    return (panda$collections$ListView$LTpanda$io$File$GT*) result;
}

String* panda$io$File$absolutePath(File* file) {
    char result[PATH_MAX];
    char* rawPath = pandaGetString(file->path);
    realpath(rawPath, result);
    return pandaNewString(result, strlen(result));
}

void panda$io$File$delete(File* file) {
    char* path = pandaGetString(file->path);
    if (remove(path)) {
        printf("failed to delete %s\n", path);
        pandaFatalError("file could not be deleted");
    }
}

Bit panda$io$File$exists(File* file) {
    char* path = pandaGetString(file->path);
    struct stat fileInfo;
    return stat(path, &fileInfo) >= 0;
}

Bit panda$io$File$isDirectory(File* file) {
    char* path = pandaGetString(file->path);
    struct stat fileInfo;
    stat(path, &fileInfo);
    return S_ISDIR(fileInfo.st_mode);
}

void panda$io$File$createDirectory(File* file) {
    char* path = pandaGetString(file->path);
    mkdir(path, 0755);
}


/***** Concurrency *****/

Thread* panda$threads$Thread$currentThread() {
    return (Thread*) pthread_getspecific(currentThreadKey);
}

void _pandaThreadEntry(Thread* thread) {
    pthread_setspecific(currentThreadKey, thread);
    panda$threads$Thread$run(thread);
    if (thread->preventsExit) {
        pthread_mutex_lock(&preventsExitThreadsMutex);
        preventsExitThreads--;
        if (preventsExitThreads == 0)
            pthread_cond_signal(&preventsExitThreadsVar);
        pthread_mutex_unlock(&preventsExitThreadsMutex);
    }
}

int panda$core$Panda$allocThreadLocal() {
    pthread_mutex_lock(&threadLock);
    int result = ++threadLocalCount;
    pthread_mutex_unlock(&threadLock);
    return result;
}

panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT* panda$core$Panda$getThreadLocals(Thread* thread) {
    return thread->threadLocals;
}

// FIXME: these are temporary, just until we have first-class functions in
// Panda itself

Bit panda$core$Panda$callBitFunction(void* f) {
    return ((Bit (*)()) f)();
}

Int8 panda$core$Panda$callInt8Function(void* f) {
    return ((Int8 (*)()) f)();
}

Int16 panda$core$Panda$callInt16Function(void* f) {
    return ((Int16 (*)()) f)();
}

Int32 panda$core$Panda$callInt32Function(void* f) {
    return ((Int32 (*)()) f)();
}

Int64 panda$core$Panda$callInt64Function(void* f) {
    return ((Int64 (*)()) f)();
}

Char panda$core$Panda$callCharFunction(void* f) {
    return ((Char (*)()) f)();
}

Real32 panda$core$Panda$callReal32Function(void* f) {
    return ((Real32 (*)()) f)();
}

Real64 panda$core$Panda$callReal64Function(void* f) {
    return ((Real64 (*)()) f)();
}

Object* panda$core$Panda$callObjectFunction(void* f) {
    return ((Object* (*)()) f)();
}

Int32 panda$threads$InternalMessageQueue$pendingMessages(
        InternalMessageQueue* msgQueue) {
    NativeQueue* queue = msgQueue->nativeQueue;
    pthread_mutex_lock(&queue->lock);
    int result = queue->pendingCount;
    pthread_mutex_unlock(&queue->lock);
    return result;
}

void assert(Bit cond, const char* message) {
    if (!cond)
        pandaFatalError(message);
}

void panda$threads$InternalMessageQueue$initMessageQueue(
        InternalMessageQueue* msgQueue) {
    msgQueue->nativeQueue = MALLOC(sizeof(NativeQueue));
    NativeQueue* nq = (NativeQueue*) msgQueue->nativeQueue;
    pthread_cond_init(&nq->cond, NULL);
    pthread_mutex_init(&nq->lock, NULL);
}

void panda$threads$InternalMessageQueue$finalize(
        InternalMessageQueue* msgQueue) {
    NativeQueue* nq = (NativeQueue*) msgQueue->nativeQueue;
    pthread_cond_destroy(&nq->cond);
    pthread_mutex_destroy(&nq->lock);
}

void panda$threads$InternalMessageQueue$sendMessage(
        InternalMessageQueue* msgQueue, Message* message) {
    NativeQueue* queue = (NativeQueue*) msgQueue->nativeQueue;
    pthread_mutex_lock(&queue->lock);
    if (queue->tail != NULL) {
        queue->tail->next = message;
        message->prev = queue->tail;
    }
    if (queue->head == NULL)
        queue->head = message;
    queue->tail = message;
    queue->pendingCount++;
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->lock);
}
          
panda$core$Object* panda$threads$InternalMessageQueue$getMessage_$RObject$Z(InternalMessageQueue* msgQueue) {
    NativeQueue* queue = msgQueue->nativeQueue;
    pthread_mutex_lock(&queue->lock);
    while (queue->head == NULL)
        pthread_cond_wait(&queue->cond, &queue->lock);
    Message* result = queue->head;
    queue->head = result->next;
    result->next = NULL;
    if (queue->head != NULL)
        queue->head->prev = NULL;
    queue->pendingCount--;
    pthread_mutex_unlock(&queue->lock);
    return result->data;
}

panda$core$Object* panda$threads$InternalMessageQueue$getMessage_Int32_$RObject$Z(InternalMessageQueue* queue, int timeout) {
    // FIXME NOT IMPLEMENTED
    UNUSED(timeout);
    return panda$threads$InternalMessageQueue$getMessage_$RObject$Z(queue);
}

void panda$threads$InternalMessageQueue$threadExit() {
    Thread* currentThread = panda$threads$Thread$currentThread();
    if (currentThread->preventsExit) {
        pthread_mutex_lock(&preventsExitThreadsMutex);
        preventsExitThreads--;
        if (preventsExitThreads == 0)
            pthread_cond_signal(&preventsExitThreadsVar);
        pthread_mutex_unlock(&preventsExitThreadsMutex);
    }
    pthread_exit(NULL);
}

void panda$threads$Thread$startThread(
        Thread* thread, 
        panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* context) {
    if (thread->preventsExit) {
        pthread_mutex_lock(&preventsExitThreadsMutex);
        preventsExitThreads++;
        pthread_mutex_unlock(&preventsExitThreadsMutex);
    }
    panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT* threadLocals = pandaNew(panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT);
    panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT$init(threadLocals);
    thread->threadLocals = threadLocals;
    panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT$$ARREQ_TYPE* hashPut =
            (panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT$$ARREQ_TYPE*) 
                *(&threadLocals->cl->vtable + 
                panda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT$$ARREQ_INDEX);    
    hashPut(threadLocals, class_panda$threads$Thread$context$index, 
            (panda$core$Object*) context);
    panda$core$BitWrapper* trueWrapper = pandaNew(panda$core$BitWrapper);
    trueWrapper->value = true;
    hashPut(threadLocals, -class_panda$threads$Thread$context$index, 
            (panda$core$Object*) trueWrapper);
    pthread_create((pthread_t*) &thread->nativeThread, NULL, 
            (threadRun) _pandaThreadEntry, thread);
}

void panda$threads$Lock$initialize(Lock* lock) {
    pthread_mutexattr_t a;
    pthread_mutexattr_init(&a);
    pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
    lock->nativeLock = MALLOC(sizeof(pthread_mutex_t));
    pthread_mutex_init(lock->nativeLock, &a);
}

void panda$threads$Lock$lock(Lock* lock) {
    pthread_mutex_lock(lock->nativeLock);
}

void panda$threads$Lock$unlock(Lock* lock) {
    pthread_mutex_unlock(lock->nativeLock);
}

void panda$threads$Lock$finalize(Lock* lock) {
    pthread_mutex_destroy(lock->nativeLock);
}


/***** Math *****/

union Real32Int32 {
    Real32 r;
    Int32 i;
};

union Real64Int64 {
    Real64 r;
    Int64 i;
};

Int32 panda$core$Int8Wrapper$length(Int8 self) {
    return 32 - __builtin_clz(self);
}

Int32 panda$core$Int16Wrapper$length(Int16 self) {
    return 32 - __builtin_clz(self);
}

Int32 panda$core$Int32Wrapper$length(Int32 self) {
    return 32 - __builtin_clz(self);
}

Int32 panda$core$Int64Wrapper$length(Int64 self) {
    UInt32 high = self >> 32;
    if (high != 0)
        return 32 - __builtin_clz(high);
    return 32 - __builtin_clz(self);
}

Int32 panda$core$UInt8Wrapper$length(UInt8 self) {
    return 32 - __builtin_clz(self);
}

Int32 panda$core$UInt16Wrapper$length(panda$core$UInt16Wrapper* self) {
    return 32 - __builtin_clz(self->value);
}

Int32 panda$core$UInt32Wrapper$length(panda$core$UInt32Wrapper* self) {
    return 32 - __builtin_clz(self->value);
}

Int32 panda$core$UInt64Wrapper$length(panda$core$UInt64Wrapper* self) {
    UInt32 high = self->value >> 32;
    if (high != 0)
        return 32 - __builtin_clz(high);
    return 32 - __builtin_clz(self->value);
}

Int32 panda$core$Panda$real32Bits(Real32 r) {
    union Real32Int32 u;
    u.r = r;
    return u.i;
}

Int64 panda$core$Panda$real64Bits(Real64 r) {
    union Real64Int64 u;
    u.r = r;
    return u.i;
}

Real32 panda$core$Real32Wrapper$sqrt(Real32 r) {
    return sqrt(r);
}

Real32 panda$core$Real32Wrapper$sin(Real32 r) {
    return sin(r);
}

Real32 panda$core$Real32Wrapper$cos(Real32 r) {
    return cos(r);
}

Real64 panda$core$Real64Wrapper$sqrt(Real64 r) {
    return sqrt(r);
}

Real64 panda$core$Real64Wrapper$sin(Real64 r) {
    return sin(r);
}

Real64 panda$core$Real64Wrapper$cos(Real64 r) {
    return cos(r);
}

Real64 panda$core$Real64Wrapper$atan2(Real64 y, Real64 x) {
    return atan2(y, x);
}

Bit panda$core$Real32Wrapper$isInfinite(Real32 r) {
    return isinf(r);
}

Bit panda$core$Real64Wrapper$isInfinite(Real64 r) {
    return isinf(r);
}

Bit panda$core$Real32Wrapper$isNaN(Real32 r) {
    return isnan(r);
}

Bit panda$core$Real64Wrapper$isNaN(Real64 r) {
    return isnan(r);
}

Real32 panda$core$Panda$pow_Real32_Real32_$RReal32(Real32 x, Real32 y) {
    return pow(x, y);
}

Real64 panda$core$Panda$pow_Real64_Real64_$RReal64(Real64 x, Real64 y) {
    return pow(x, y);
}

Real32 panda$core$Panda$pow_Real32_Int32_$RReal32(Real32 x, Int32 y) {
    return pow(x, y);
}

Real64 panda$core$Panda$pow_Real64_Int32_$RReal64(Real64 x, Int32 y) {
    return pow(x, y);
}


/***** Regex *****/

// we have to manually hang on to the text pointer, because the garbage 
// collector evidently isn't "seeing" ICU's pointer to it and is thus collecting
// it
typedef struct NativeRegex {
    URegularExpression* regex;
    char* text;
} NativeRegex;

void panda$core$RegularExpression$compile(RegularExpression* r, String* regex, 
        Int32 flags) {
    UErrorCode status = U_ZERO_ERROR;
    char* text = pandaGetString(regex);
    UText* ut = utext_openUTF8(NULL, text, regex->chars->$length, &status);
    UParseError parseStatus;
    int icuFlags = 0;
    if (flags & 1)
        icuFlags |= UREGEX_MULTILINE;
    r->nativeHandle = MALLOC(sizeof(NativeRegex));
    ((NativeRegex*) r->nativeHandle)->regex = uregex_openUText(ut, icuFlags, 
            &parseStatus, &status);
    utext_close(ut);
    if (U_FAILURE(status))
        pandaFatalError(u_errorName(status));
}

RegularExpression* panda$core$RegularExpression$clone(RegularExpression* r) {
    RegularExpression* result = pandaNew(panda$core$RegularExpression);
    UErrorCode status = U_ZERO_ERROR;
    URegularExpression* ur = ((NativeRegex*) (r->nativeHandle))->regex;
    result->nativeHandle = MALLOC(sizeof(NativeRegex));
    ((NativeRegex*) result->nativeHandle)->regex = uregex_clone(ur, &status);
    if (U_FAILURE(status))
        pandaFatalError(u_errorName(status));
    return result;
}

void panda$core$Matcher$setText(void* nr, String* text) {
    UErrorCode status = U_ZERO_ERROR;
    char* utf8 = pandaGetString(text);
    ((NativeRegex*) nr)->text = utf8;
    UText* ut = utext_openUTF8(NULL, utf8, 
            text->chars->$length, &status);
    uregex_setUText(((NativeRegex*) nr)->regex, ut, &status);
    utext_close(ut);
    if (U_FAILURE(status))
        pandaFatalError(u_errorName(status));
}

Bit panda$core$Matcher$matches_$NativePointer_$RBit(void* nr) {
    UErrorCode status = U_ZERO_ERROR;
    Bit result = uregex_matches(((NativeRegex*) nr)->regex, 0, &status);
    if (U_FAILURE(status))
        pandaFatalError(u_errorName(status));
    return result;
}

Bit panda$core$Matcher$find_$NativePointer_Int32_$RBit(void* nr, Int32 startIndex) {
    UErrorCode status = U_ZERO_ERROR;
    Bit result = uregex_find(((NativeRegex*) nr)->regex, startIndex, &status);
    if (U_FAILURE(status))
        pandaFatalError(u_errorName(status));
    return result;
}

/*
 * Convert a UText to a panda String, closing the UText afterwards.
 */
String* pandaUTextToString(UText* ut, int length) {
    // NOTE: we are making the (usually unsafe) assumption that the UText
    // contains UTF-8 characters, so we can just do a straight copy out rather
    // than bother with conversion. As we are working exclusively in UTF-8,
    // this should always be true. 
    const char* utf8 = (ut->context + (int) UTEXT_GETNATIVEINDEX(ut));
    String* result = pandaNewString(utf8, length);
    utext_close(ut);
    return result;
}

Int32 panda$core$Matcher$groupCount_$NativePointer_$RInt32(void* nr) {
    UErrorCode status = U_ZERO_ERROR;
    Int32 result = uregex_groupCount(((NativeRegex*) nr)->regex, &status);
    if (U_FAILURE(status))
        pandaFatalError(u_errorName(status));
    return result + 1;
}

String* panda$core$Matcher$group_$NativePointer_Int32_$RString(void* nr, Int32 group) {
    UErrorCode status = U_ZERO_ERROR;
    int64_t length;
    UText* ut = uregex_groupUText(((NativeRegex*) nr)->regex, group, NULL,
            &length, &status);
    if (U_FAILURE(status))
        pandaFatalError(u_errorName(status));
    return pandaUTextToString(ut, length);
}

Int32 panda$core$Matcher$start_$NativePointer_$RInt32(void* nr) {
    UErrorCode status = U_ZERO_ERROR;
    Int32 result = uregex_start(((NativeRegex*) nr)->regex, 0, &status);
    if (U_FAILURE(status))
        pandaFatalError(u_errorName(status));
    return result;
}

Int32 panda$core$Matcher$end_$NativePointer_$RInt32(void* nr) {
    UErrorCode status = U_ZERO_ERROR;
    Int32 result = uregex_end(((NativeRegex*) nr)->regex, 0, &status);
    if (U_FAILURE(status))
        pandaFatalError(u_errorName(status));
    return result;
}

void panda$core$RegularExpression$close(RegularExpression* r) {
    uregex_close(((NativeRegex*) r->nativeHandle)->regex);
    FREE(r->nativeHandle);
    r->nativeHandle = NULL;
}


/***** Debug *****/

void panda$core$Panda$debugWrite_Int32(Int32 v) {
    printf("Debug: %d\n", v);
}

void panda$core$Panda$debugWritePointer(Object* v) {
    printf("Debug: %p\n", v);
}

void panda$core$Panda$debugWrite$Object(Object* o) {
    char* name = pandaGetString(o->cl->name);
    printf("Debug: %p (%s)\n", o, name);
}





#undef pandaNew

Object* pandaNew(Class* class_ptr, Int32 size) {
    return _pandaNew(class_ptr, size);
}
