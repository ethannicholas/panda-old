// This file was automatically generated by the Panda compiler
#ifndef panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT_H
#define panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT_H
extern panda$core$Class panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT_class;
#ifndef CLASS_panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT
#define CLASS_panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT
struct panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT {
    panda$core$Class* cl;
    panda$core$UnsignedInteger* end;
    panda$core$Integer* step;
    panda$core$UnsignedInteger* current;
    Bit endInclusive;
    Bit isDone;
};

#define panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT$get_done_$Rpanda$core$Bit_INDEX 4
typedef Bit(panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT$get_done_$Rpanda$core$Bit_TYPE)(panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT* self);
#define panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT$next_$Rpanda$core$UnsignedInteger_INDEX 8
typedef panda$core$UnsignedInteger*(panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT$next_$Rpanda$core$UnsignedInteger_TYPE)(panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT* self);
void panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT$init_panda$core$UnsignedInteger_panda$core$UnsignedInteger_panda$core$Integer_Bit(panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT* self, panda$core$UnsignedInteger*, panda$core$UnsignedInteger*, panda$core$Integer*, Bit);
panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT* new_panda$core$UIntIterator$LTpanda$core$UnsignedInteger$Cpanda$core$Integer$GT$init_panda$core$UnsignedInteger_panda$core$UnsignedInteger_panda$core$Integer_Bit(panda$core$UnsignedInteger*, panda$core$UnsignedInteger*, panda$core$Integer*, Bit);
#endif
#endif
