// This file was automatically generated by the Panda compiler
#ifndef panda$collections$FilterIterator$LTpanda$core$UInt32$GT_H
#define panda$collections$FilterIterator$LTpanda$core$UInt32$GT_H
extern panda$core$Class panda$collections$FilterIterator$LTpanda$core$UInt32$GT_class;
#ifndef CLASS_panda$collections$FilterIterator$LTpanda$core$UInt32$GT
#define CLASS_panda$collections$FilterIterator$LTpanda$core$UInt32$GT
struct panda$collections$FilterIterator$LTpanda$core$UInt32$GT {
    panda$core$Class* cl;
    panda$collections$Iterator$LTpanda$core$UInt32$GT* base;
    void** filter;
    panda$core$UInt32Wrapper* nextValue;
};

#define panda$collections$FilterIterator$LTpanda$core$UInt32$GT$get_done_$Rpanda$core$Bit_INDEX 4
typedef Bit(panda$collections$FilterIterator$LTpanda$core$UInt32$GT$get_done_$Rpanda$core$Bit_TYPE)(panda$collections$FilterIterator$LTpanda$core$UInt32$GT* self);
#define panda$collections$FilterIterator$LTpanda$core$UInt32$GT$next_$Rpanda$core$UInt32_INDEX 8
typedef UInt32(panda$collections$FilterIterator$LTpanda$core$UInt32$GT$next_$Rpanda$core$UInt32_TYPE)(panda$collections$FilterIterator$LTpanda$core$UInt32$GT* self);
#define panda$collections$FilterIterator$LTpanda$core$UInt32$GT$getNext_INDEX 9
typedef void(panda$collections$FilterIterator$LTpanda$core$UInt32$GT$getNext_TYPE)(panda$collections$FilterIterator$LTpanda$core$UInt32$GT* self);
void panda$collections$FilterIterator$LTpanda$core$UInt32$GT$init_panda$collections$Iterator$LTpanda$core$UInt32$GT_$LPpanda$core$UInt32$RP$EQ$GT$LPpanda$core$Bit$RP(panda$collections$FilterIterator$LTpanda$core$UInt32$GT* self, panda$collections$Iterator$LTpanda$core$UInt32$GT*, void**);
panda$collections$FilterIterator$LTpanda$core$UInt32$GT* new_panda$collections$FilterIterator$LTpanda$core$UInt32$GT$init_panda$collections$Iterator$LTpanda$core$UInt32$GT_$LPpanda$core$UInt32$RP$EQ$GT$LPpanda$core$Bit$RP(panda$collections$Iterator$LTpanda$core$UInt32$GT*, void**);
#endif
#endif