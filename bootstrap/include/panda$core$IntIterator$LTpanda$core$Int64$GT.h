// This file was automatically generated by the Panda compiler
#ifndef panda$core$IntIterator$LTpanda$core$Int64$GT_H
#define panda$core$IntIterator$LTpanda$core$Int64$GT_H
extern panda$core$Class panda$core$IntIterator$LTpanda$core$Int64$GT_class;
#ifndef CLASS_panda$core$IntIterator$LTpanda$core$Int64$GT
#define CLASS_panda$core$IntIterator$LTpanda$core$Int64$GT
struct panda$core$IntIterator$LTpanda$core$Int64$GT {
    panda$core$Class* cl;
    Int64 end;
    Int64 step;
    Int64 current;
    Bit endInclusive;
    Bit isDone;
};

#define panda$core$IntIterator$LTpanda$core$Int64$GT$get_done_$Rpanda$core$Bit_INDEX 4
typedef Bit(panda$core$IntIterator$LTpanda$core$Int64$GT$get_done_$Rpanda$core$Bit_TYPE)(panda$core$IntIterator$LTpanda$core$Int64$GT* self);
#define panda$core$IntIterator$LTpanda$core$Int64$GT$next_$Rpanda$core$Int64_INDEX 8
typedef Int64(panda$core$IntIterator$LTpanda$core$Int64$GT$next_$Rpanda$core$Int64_TYPE)(panda$core$IntIterator$LTpanda$core$Int64$GT* self);
void panda$core$IntIterator$LTpanda$core$Int64$GT$init_Int64_Int64_Int64_Bit(panda$core$IntIterator$LTpanda$core$Int64$GT* self, Int64, Int64, Int64, Bit);
panda$core$IntIterator$LTpanda$core$Int64$GT* new_panda$core$IntIterator$LTpanda$core$Int64$GT$init_Int64_Int64_Int64_Bit(Int64, Int64, Int64, Bit);
#endif
#endif
