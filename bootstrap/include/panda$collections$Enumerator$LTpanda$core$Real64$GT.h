// This file was automatically generated by the Panda compiler
#ifndef panda$collections$Enumerator$LTpanda$core$Real64$GT_H
#define panda$collections$Enumerator$LTpanda$core$Real64$GT_H
extern panda$core$Class panda$collections$Enumerator$LTpanda$core$Real64$GT_class;
#ifndef CLASS_panda$collections$Enumerator$LTpanda$core$Real64$GT
#define CLASS_panda$collections$Enumerator$LTpanda$core$Real64$GT
struct panda$collections$Enumerator$LTpanda$core$Real64$GT {
    panda$core$Class* cl;
    panda$collections$Iterator$LTpanda$core$Real64$GT* base;
    Int64 index;
};

#define panda$collections$Enumerator$LTpanda$core$Real64$GT$get_done_$Rpanda$core$Bit_INDEX 4
typedef Bit(panda$collections$Enumerator$LTpanda$core$Real64$GT$get_done_$Rpanda$core$Bit_TYPE)(panda$collections$Enumerator$LTpanda$core$Real64$GT* self);
#define panda$collections$Enumerator$LTpanda$core$Real64$GT$next_$R$LPpanda$core$Int64$Cpanda$core$Real64$RP_INDEX 8
typedef $LPInt64$CReal64$RP*(panda$collections$Enumerator$LTpanda$core$Real64$GT$next_$R$LPpanda$core$Int64$Cpanda$core$Real64$RP_TYPE)(panda$collections$Enumerator$LTpanda$core$Real64$GT* self);
void panda$collections$Enumerator$LTpanda$core$Real64$GT$init_panda$collections$CollectionView$LTpanda$core$Real64$GT(panda$collections$Enumerator$LTpanda$core$Real64$GT* self, panda$collections$CollectionView$LTpanda$core$Real64$GT*);
panda$collections$Enumerator$LTpanda$core$Real64$GT* new_panda$collections$Enumerator$LTpanda$core$Real64$GT$init_panda$collections$CollectionView$LTpanda$core$Real64$GT(panda$collections$CollectionView$LTpanda$core$Real64$GT*);
#endif
#endif
