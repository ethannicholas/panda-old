// This file was automatically generated by the Panda compiler
#ifndef panda$collections$Enumerator$LTpanda$core$Char$GT_H
#define panda$collections$Enumerator$LTpanda$core$Char$GT_H
extern panda$core$Class panda$collections$Enumerator$LTpanda$core$Char$GT_class;
#ifndef CLASS_panda$collections$Enumerator$LTpanda$core$Char$GT
#define CLASS_panda$collections$Enumerator$LTpanda$core$Char$GT
struct panda$collections$Enumerator$LTpanda$core$Char$GT {
    panda$core$Class* cl;
    panda$collections$Iterator$LTpanda$core$Char$GT* base;
    Int64 index;
};

#define panda$collections$Enumerator$LTpanda$core$Char$GT$get_done_$Rpanda$core$Bit_INDEX 4
typedef Bit(panda$collections$Enumerator$LTpanda$core$Char$GT$get_done_$Rpanda$core$Bit_TYPE)(panda$collections$Enumerator$LTpanda$core$Char$GT* self);
#define panda$collections$Enumerator$LTpanda$core$Char$GT$next_$R$LPpanda$core$Int64$Cpanda$core$Char$RP_INDEX 8
typedef $LPInt64$CChar$RP*(panda$collections$Enumerator$LTpanda$core$Char$GT$next_$R$LPpanda$core$Int64$Cpanda$core$Char$RP_TYPE)(panda$collections$Enumerator$LTpanda$core$Char$GT* self);
void panda$collections$Enumerator$LTpanda$core$Char$GT$init_panda$collections$CollectionView$LTpanda$core$Char$GT(panda$collections$Enumerator$LTpanda$core$Char$GT* self, panda$collections$CollectionView$LTpanda$core$Char$GT*);
panda$collections$Enumerator$LTpanda$core$Char$GT* new_panda$collections$Enumerator$LTpanda$core$Char$GT$init_panda$collections$CollectionView$LTpanda$core$Char$GT(panda$collections$CollectionView$LTpanda$core$Char$GT*);
#endif
#endif