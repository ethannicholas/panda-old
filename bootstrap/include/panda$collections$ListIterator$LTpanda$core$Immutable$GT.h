// This file was automatically generated by the Panda compiler
#ifndef panda$collections$ListIterator$LTpanda$core$Immutable$GT_H
#define panda$collections$ListIterator$LTpanda$core$Immutable$GT_H
extern panda$core$Class panda$collections$ListIterator$LTpanda$core$Immutable$GT_class;
#ifndef CLASS_panda$collections$ListIterator$LTpanda$core$Immutable$GT
#define CLASS_panda$collections$ListIterator$LTpanda$core$Immutable$GT
struct panda$collections$ListIterator$LTpanda$core$Immutable$GT {
    panda$core$Class* cl;
    panda$collections$ListView$LTpanda$core$Immutable$GT* list;
    Int64 index;
};

#define panda$collections$ListIterator$LTpanda$core$Immutable$GT$get_done_$Rpanda$core$Bit_INDEX 4
typedef Bit(panda$collections$ListIterator$LTpanda$core$Immutable$GT$get_done_$Rpanda$core$Bit_TYPE)(panda$collections$ListIterator$LTpanda$core$Immutable$GT* self);
#define panda$collections$ListIterator$LTpanda$core$Immutable$GT$next_$Rpanda$core$Immutable_INDEX 8
typedef panda$core$Immutable*(panda$collections$ListIterator$LTpanda$core$Immutable$GT$next_$Rpanda$core$Immutable_TYPE)(panda$collections$ListIterator$LTpanda$core$Immutable$GT* self);
void panda$collections$ListIterator$LTpanda$core$Immutable$GT$init_panda$collections$ListView$LTpanda$core$Immutable$GT(panda$collections$ListIterator$LTpanda$core$Immutable$GT* self, panda$collections$ListView$LTpanda$core$Immutable$GT*);
panda$collections$ListIterator$LTpanda$core$Immutable$GT* new_panda$collections$ListIterator$LTpanda$core$Immutable$GT$init_panda$collections$ListView$LTpanda$core$Immutable$GT(panda$collections$ListView$LTpanda$core$Immutable$GT*);
#endif
#endif
