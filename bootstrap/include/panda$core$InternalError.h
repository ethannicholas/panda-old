// This file was automatically generated by the Panda compiler
#ifndef panda$core$InternalError_H
#define panda$core$InternalError_H
extern panda$core$Class panda$core$InternalError_class;
#ifndef CLASS_panda$core$InternalError
#define CLASS_panda$core$InternalError
struct panda$core$InternalError {
    panda$core$Class* cl;
    panda$core$String* message;
    panda$collections$ImmutablePrimitiveArray$LTpanda$core$StackTraceEntry$GT* stack;
};

void panda$core$InternalError$init(panda$core$InternalError* self);
panda$core$InternalError* new_panda$core$InternalError$init();
void panda$core$InternalError$init_panda$core$String(panda$core$InternalError* self, panda$core$String*);
panda$core$InternalError* new_panda$core$InternalError$init_panda$core$String(panda$core$String*);
#endif
#endif
