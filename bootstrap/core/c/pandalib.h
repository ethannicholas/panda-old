#ifndef PANDALIB_
#define PANDALIB_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <stdarg.h>
#include <inttypes.h>
#include "panda_base.h"
#include "panda.h"

#define true 1
#define false 0
#define PATH_MAX 4096

typedef panda$core$Object Object;
typedef panda$core$Class Class;
typedef panda$collections$PrimitiveArray PrimitiveArray;
typedef panda$core$String String;
typedef panda$collections$PrimitiveArray$LTpanda$core$String$GT String$Array;
typedef panda$io$File File;
typedef panda$core$Error Error;
typedef panda$core$RegularExpression RegularExpression;
typedef panda$threads$Message Message;
typedef panda$threads$InternalMessageQueue InternalMessageQueue;
typedef panda$threads$Thread Thread;
typedef panda$threads$Lock Lock;

typedef struct NativeQueue {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int pendingCount;
    Message* head;
    Message* tail;
} NativeQueue;

typedef struct _nativeException {
    Int64			 exception_class;
    void* exception_cleanup;
    Int64			 private_1;
    Int64			 private_2;
    Error*       pandaException;
} _nativeException;

// "PNDAPNDA"
#define EXCEPTION_CLASS 0x504e4441504e4441L

void* pandaGetInterfaceMethod(panda$core$Object* o, panda$core$Class* intf, 
        int index);

Object* _pandaNew(Class* class_ptr, Int size);

#define pandaNew(CLASS) ((CLASS*) _pandaNew((Class*) & CLASS ## _class, sizeof(CLASS)))

String* pandaNewString(const char* chars, Int byteLength);

PrimitiveArray* pandaNewPrimitiveArrayWithLength(Class* class_ptr, Int length, 
        Int elementSize, Bit elementsArePointers);

PrimitiveArray* pandaNewPrimitiveArrayCopy(Class* class_ptr, 
        PrimitiveArray* array, Int elementSize, Bit elementsArePointers);

PrimitiveArray* pandaNewPrimitiveArrayWithValues(Class* class_ptr, Int length, 
        Int elementType, ...);

void pandaCheckBounds(PrimitiveArray* array, Int index);

void pandaCheckOverflow(Bit flag);

char* pandaGetString(String* s);

void pandaThrow(Error* e);

void pandaFatalError(const char* msg);

#endif