// This file was automatically generated by the Panda compiler
#ifndef panda$parser$GLRParser$Action_H
#define panda$parser$GLRParser$Action_H
extern panda$core$Class panda$parser$GLRParser$Action_class;
#ifndef CLASS_panda$parser$GLRParser$Action
#define CLASS_panda$parser$GLRParser$Action
struct panda$parser$GLRParser$Action {
    panda$core$Class* cl;
    panda$parser$GLRParser$Action$Type* type;
    Int64 target;
    panda$collections$Array$LTpanda$parser$GLRParser$Action$GT* subactions;
};

#define panda$parser$GLRParser$Action$convert_$Rpanda$core$String_INDEX 1
typedef panda$core$String*(panda$parser$GLRParser$Action$convert_$Rpanda$core$String_TYPE)(panda$parser$GLRParser$Action* self);
#define panda$parser$GLRParser$Action$$EQ_panda$core$Object_$Rpanda$core$Bit_INDEX 2
typedef Bit(panda$parser$GLRParser$Action$$EQ_panda$core$Object_$Rpanda$core$Bit_TYPE)(panda$parser$GLRParser$Action* self, panda$core$Object*);
#define panda$parser$GLRParser$Action$get_hash_$Rpanda$core$Int64_INDEX 3
typedef Int64(panda$parser$GLRParser$Action$get_hash_$Rpanda$core$Int64_TYPE)(panda$parser$GLRParser$Action* self);
void panda$parser$GLRParser$Action$init_panda$parser$GLRParser$Action$Type_Int64(panda$parser$GLRParser$Action* self, panda$parser$GLRParser$Action$Type*, Int64);
panda$parser$GLRParser$Action* new_panda$parser$GLRParser$Action$init_panda$parser$GLRParser$Action$Type_Int64(panda$parser$GLRParser$Action$Type*, Int64);
void panda$parser$GLRParser$Action$init_panda$collections$ListView$LTpanda$parser$GLRParser$Action$GT(panda$parser$GLRParser$Action* self, panda$collections$ListView$LTpanda$parser$GLRParser$Action$GT*);
panda$parser$GLRParser$Action* new_panda$parser$GLRParser$Action$init_panda$collections$ListView$LTpanda$parser$GLRParser$Action$GT(panda$collections$ListView$LTpanda$parser$GLRParser$Action$GT*);
#endif
#endif
