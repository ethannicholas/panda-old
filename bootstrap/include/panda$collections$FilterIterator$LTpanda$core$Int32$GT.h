// This file was automatically generated by the Panda compiler
#ifndef panda$collections$FilterIterator$LTpanda$core$Int32$GT_H
#define panda$collections$FilterIterator$LTpanda$core$Int32$GT_H
extern panda$core$Class panda$collections$FilterIterator$LTpanda$core$Int32$GT_class;
#ifndef CLASS_panda$collections$FilterIterator$LTpanda$core$Int32$GT
#define CLASS_panda$collections$FilterIterator$LTpanda$core$Int32$GT
struct panda$collections$FilterIterator$LTpanda$core$Int32$GT {
    panda$core$Class* cl;
    panda$collections$Iterator$LTpanda$core$Int32$GT* base;
    void** filter;
    panda$core$Int32Wrapper* nextValue;
};

#define panda$collections$FilterIterator$LTpanda$core$Int32$GT$get_done_$Rpanda$core$Bit_INDEX 4
typedef Bit(panda$collections$FilterIterator$LTpanda$core$Int32$GT$get_done_$Rpanda$core$Bit_TYPE)(panda$collections$FilterIterator$LTpanda$core$Int32$GT* self);
#define panda$collections$FilterIterator$LTpanda$core$Int32$GT$next_$Rpanda$core$Int32_INDEX 8
typedef Int32(panda$collections$FilterIterator$LTpanda$core$Int32$GT$next_$Rpanda$core$Int32_TYPE)(panda$collections$FilterIterator$LTpanda$core$Int32$GT* self);
#define panda$collections$FilterIterator$LTpanda$core$Int32$GT$getNext_INDEX 9
typedef void(panda$collections$FilterIterator$LTpanda$core$Int32$GT$getNext_TYPE)(panda$collections$FilterIterator$LTpanda$core$Int32$GT* self);
void panda$collections$FilterIterator$LTpanda$core$Int32$GT$init_panda$collections$Iterator$LTpanda$core$Int32$GT_$LPpanda$core$Int32$RP$EQ$GT$LPpanda$core$Bit$RP(panda$collections$FilterIterator$LTpanda$core$Int32$GT* self, panda$collections$Iterator$LTpanda$core$Int32$GT*, void**);
panda$collections$FilterIterator$LTpanda$core$Int32$GT* new_panda$collections$FilterIterator$LTpanda$core$Int32$GT$init_panda$collections$Iterator$LTpanda$core$Int32$GT_$LPpanda$core$Int32$RP$EQ$GT$LPpanda$core$Bit$RP(panda$collections$Iterator$LTpanda$core$Int32$GT*, void**);
#endif
#endif