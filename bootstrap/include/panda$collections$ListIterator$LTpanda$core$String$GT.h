// This file was automatically generated by the Panda compiler
#ifndef panda$collections$ListIterator$LTpanda$core$String$GT_H
#define panda$collections$ListIterator$LTpanda$core$String$GT_H
extern panda$core$Class panda$collections$ListIterator$LTpanda$core$String$GT_class;
#ifndef CLASS_panda$collections$ListIterator$LTpanda$core$String$GT
#define CLASS_panda$collections$ListIterator$LTpanda$core$String$GT
struct panda$collections$ListIterator$LTpanda$core$String$GT {
    panda$core$Class* cl;
    panda$collections$ListView$LTpanda$core$String$GT* list;
    Int64 index;
};

#define panda$collections$ListIterator$LTpanda$core$String$GT$get_done_$Rpanda$core$Bit_INDEX 4
typedef Bit(panda$collections$ListIterator$LTpanda$core$String$GT$get_done_$Rpanda$core$Bit_TYPE)(panda$collections$ListIterator$LTpanda$core$String$GT* self);
#define panda$collections$ListIterator$LTpanda$core$String$GT$next_$Rpanda$core$String_INDEX 8
typedef panda$core$String*(panda$collections$ListIterator$LTpanda$core$String$GT$next_$Rpanda$core$String_TYPE)(panda$collections$ListIterator$LTpanda$core$String$GT* self);
void panda$collections$ListIterator$LTpanda$core$String$GT$init_panda$collections$ListView$LTpanda$core$String$GT(panda$collections$ListIterator$LTpanda$core$String$GT* self, panda$collections$ListView$LTpanda$core$String$GT*);
panda$collections$ListIterator$LTpanda$core$String$GT* new_panda$collections$ListIterator$LTpanda$core$String$GT$init_panda$collections$ListView$LTpanda$core$String$GT(panda$collections$ListView$LTpanda$core$String$GT*);
#endif
#endif