// This file was automatically generated by the Panda compiler
#ifndef panda$util$JSON_H
#define panda$util$JSON_H
extern panda$core$Class panda$util$JSON_class;
#ifndef CLASS_panda$util$JSON
#define CLASS_panda$util$JSON
struct panda$util$JSON {
    panda$core$Class* cl;
};

void panda$util$JSON$init(panda$util$JSON* self);
panda$util$JSON* new_panda$util$JSON$init();
panda$core$Object* panda$util$JSON$parse_class_panda$core$String_$Rpanda$core$Object(panda$core$String*);
panda$core$UInt64Wrapper* panda$util$JSON$parseInt_class_panda$core$String_UInt8_$Rpanda$core$UInt64Wrapper$Z(panda$core$String*, UInt8);
#endif
#endif