// This file was automatically generated by the Panda compiler
#ifndef panda$collections$Enumerator$LTpanda$core$String$GT_H
#define panda$collections$Enumerator$LTpanda$core$String$GT_H
extern panda$core$Class panda$collections$Enumerator$LTpanda$core$String$GT_class;
#ifndef CLASS_panda$collections$Enumerator$LTpanda$core$String$GT
#define CLASS_panda$collections$Enumerator$LTpanda$core$String$GT
struct panda$collections$Enumerator$LTpanda$core$String$GT {
    panda$core$Class* cl;
    panda$collections$Iterator$LTpanda$core$String$GT* base;
    Int64 index;
};

#define panda$collections$Enumerator$LTpanda$core$String$GT$get_done_$Rpanda$core$Bit_INDEX 4
typedef Bit(panda$collections$Enumerator$LTpanda$core$String$GT$get_done_$Rpanda$core$Bit_TYPE)(panda$collections$Enumerator$LTpanda$core$String$GT* self);
#define panda$collections$Enumerator$LTpanda$core$String$GT$next_$R$LPpanda$core$Int64$Cpanda$core$String$RP_INDEX 8
typedef $LPInt64$Cpanda$core$String$RP*(panda$collections$Enumerator$LTpanda$core$String$GT$next_$R$LPpanda$core$Int64$Cpanda$core$String$RP_TYPE)(panda$collections$Enumerator$LTpanda$core$String$GT* self);
void panda$collections$Enumerator$LTpanda$core$String$GT$init_panda$collections$CollectionView$LTpanda$core$String$GT(panda$collections$Enumerator$LTpanda$core$String$GT* self, panda$collections$CollectionView$LTpanda$core$String$GT*);
panda$collections$Enumerator$LTpanda$core$String$GT* new_panda$collections$Enumerator$LTpanda$core$String$GT$init_panda$collections$CollectionView$LTpanda$core$String$GT(panda$collections$CollectionView$LTpanda$core$String$GT*);
#endif
#endif
