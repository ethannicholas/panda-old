// This file was automatically generated by the Panda compiler
#ifndef panda$core$System$Type_H
#define panda$core$System$Type_H
extern panda$core$Class panda$core$System$Type_class;
#ifndef CLASS_panda$core$System$Type
#define CLASS_panda$core$System$Type
struct panda$core$System$Type {
    panda$core$Class* cl;
};

#define panda$core$System$Type$convert_$Rpanda$core$String_INDEX 1
typedef panda$core$String*(panda$core$System$Type$convert_$Rpanda$core$String_TYPE)(panda$core$System$Type* self);
#define panda$core$System$Type$convert_$Rpanda$core$Int64_INDEX 4
typedef Int64(panda$core$System$Type$convert_$Rpanda$core$Int64_TYPE)(panda$core$System$Type* self);
void panda$core$System$Type$$classInit_class();
void panda$core$System$Type$init(panda$core$System$Type* self);
panda$core$System$Type* new_panda$core$System$Type$init();
panda$core$System$Type* panda$core$System$Type$fromInt_class_Int64_$Rpanda$core$System$Type(Int64);
panda$core$System$Type* panda$core$System$Type$fromString_class_panda$core$String_$Rpanda$core$System$Type(panda$core$String*);
extern panda$core$System$Type* class_panda$core$System$Type$NATIVE;
extern panda$core$System$Type* class_panda$core$System$Type$JAVASCRIPT;
extern panda$core$System$Type* class_panda$core$System$Type$JVM;
extern Bit class_panda$core$System$Type$$classInited;
#endif
#endif