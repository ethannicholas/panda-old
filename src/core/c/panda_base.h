#ifndef PANDA_BASE
#define PANDA_BASE

// obviously, garbage collection *has* to be enabled if you ever want any memory
// to be freed, but sometimes it is useful to disable it for debugging purposes
#define GC
#ifdef GC

#define GC_THREADS
#define GC_PTHREADS
#include "gc.h"

#define calloc error_use_MALLOC_instead
#define malloc error_use_MALLOC_instead
#define realloc error_use_REALLOC_instead
#define free error_use_FREE_instead
#define MALLOC GC_malloc_ignore_off_page
#define MALLOC_ATOMIC malloc_atomic
#define FREE GC_FREE
#define REALLOC GC_REALLOC

#else

#include <pthread.h>
#define MALLOC malloc_zero
#define MALLOC_ATOMIC MALLOC
#define REALLOC realloc
#define FREE free

#endif

typedef uint8_t Bit;
typedef int8_t Int8;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int64_t Int64;
typedef uint8_t UInt8;
typedef uint16_t UInt16;
typedef uint32_t UInt32;
typedef uint64_t UInt64;
typedef float Real32;
typedef double Real64;
typedef uint16_t Char;

typedef struct itable {
    struct panda$core$Class* cl;
    struct itable* next;
    void* methods[];
} itable;

#endif