// This file was automatically generated by the Panda compiler
#ifndef panda$core$RealNumber_H
#define panda$core$RealNumber_H
extern panda$core$Class panda$core$RealNumber_class;
#ifndef CLASS_panda$core$RealNumber
#define CLASS_panda$core$RealNumber
struct panda$core$RealNumber {
    panda$core$Class* cl;
};

#define panda$core$RealNumber$english_$Rpanda$core$String_INDEX 5
typedef panda$core$String*(panda$core$RealNumber$english_$Rpanda$core$String_TYPE)(panda$core$RealNumber* self);
#define panda$core$RealNumber$roman_$Rpanda$core$String_INDEX 17
typedef panda$core$String*(panda$core$RealNumber$roman_$Rpanda$core$String_TYPE)(panda$core$RealNumber* self);
void panda$core$RealNumber$init(panda$core$RealNumber* self);
panda$core$RealNumber* new_panda$core$RealNumber$init();
#endif
#endif