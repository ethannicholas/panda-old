// This file was automatically generated by the Panda compiler
#ifndef panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT_H
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT_H
extern panda$core$Class panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT_class;
#ifndef CLASS_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT
#define CLASS_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT
struct panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT {
    panda$core$Class* cl;
    Int64 _length;
    panda$collections$PrimitiveArray$LTpanda$collections$MutableMapEntry$LTpanda$core$Immutable$Cpanda$core$Object$GT$Z$GT* contents;
    Int64 threshold;
    Int64 changeCount;
};

#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$convert_$Rpanda$core$String_INDEX 1
typedef panda$core$String*(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$convert_$Rpanda$core$String_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$$EQ_panda$core$Object_$Rpanda$core$Bit_INDEX 2
typedef Bit(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$$EQ_panda$core$Object_$Rpanda$core$Bit_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$core$Object*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$addAll_panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Object$GT_INDEX 4
typedef void(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$addAll_panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Object$GT_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Object$GT*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$remove_panda$core$Immutable_INDEX 5
typedef void(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$remove_panda$core$Immutable_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$core$Immutable*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$$ARREQ_panda$core$Immutable_panda$core$Object_INDEX 6
typedef void(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$$ARREQ_panda$core$Immutable_panda$core$Object_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$core$Immutable*, panda$core$Object*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$clear_INDEX 7
typedef void(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$clear_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$get_iterator_$Rpanda$collections$Iterator$LT$LPpanda$core$Immutable$Cpanda$core$Object$RP$GT_INDEX 8
typedef panda$collections$Iterator$LT$LPpanda$core$Immutable$Cpanda$core$Object$RP$GT*(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$get_iterator_$Rpanda$collections$Iterator$LT$LPpanda$core$Immutable$Cpanda$core$Object$RP$GT_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$get_count_$Rpanda$core$Int64_INDEX 10
typedef Int64(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$get_count_$Rpanda$core$Int64_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$$ARR_panda$core$Immutable_$Rpanda$core$Object$Z_INDEX 12
typedef panda$core$Object*(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$$ARR_panda$core$Immutable_$Rpanda$core$Object$Z_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$core$Immutable*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$contains_panda$core$Immutable_$Rpanda$core$Bit_INDEX 13
typedef Bit(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$contains_panda$core$Immutable_$Rpanda$core$Bit_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$core$Immutable*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$get_iterator_$Rpanda$collections$Iterator$LTpanda$core$Object$Z$GT_INDEX 14
typedef panda$collections$Iterator$LTpanda$core$Object$Z$GT*(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$get_iterator_$Rpanda$collections$Iterator$LTpanda$core$Object$Z$GT_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init();
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init_panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT_panda$collections$PrimitiveArray$LTpanda$core$Object$GT(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT*, panda$collections$PrimitiveArray$LTpanda$core$Object$GT*);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init_panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT_panda$collections$PrimitiveArray$LTpanda$core$Object$GT(panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT*, panda$collections$PrimitiveArray$LTpanda$core$Object$GT*);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init_panda$collections$ListView$LTpanda$core$Immutable$GT_panda$collections$ListView$LTpanda$core$Object$GT(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$collections$ListView$LTpanda$core$Immutable$GT*, panda$collections$ListView$LTpanda$core$Object$GT*);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init_panda$collections$ListView$LTpanda$core$Immutable$GT_panda$collections$ListView$LTpanda$core$Object$GT(panda$collections$ListView$LTpanda$core$Immutable$GT*, panda$collections$ListView$LTpanda$core$Object$GT*);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init_panda$collections$ListView$LT$LPpanda$core$Immutable$Cpanda$core$Object$RP$GT(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$collections$ListView$LT$LPpanda$core$Immutable$Cpanda$core$Object$RP$GT*);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init_panda$collections$ListView$LT$LPpanda$core$Immutable$Cpanda$core$Object$RP$GT(panda$collections$ListView$LT$LPpanda$core$Immutable$Cpanda$core$Object$RP$GT*);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init_panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Object$GT(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Object$GT*);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$init_panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Object$GT(panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Object$GT*);
Int64 panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$indexFor_panda$core$Immutable_$Rpanda$core$Int64(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self, panda$core$Immutable*);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT$incrementLength(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Object$GT* self);
extern Int64 class_panda$collections$HashMap$DEFAULT_LENGTH;
extern Real64 class_panda$collections$HashMap$LOAD_FACTOR;
extern Bit class_panda$collections$HashMap$$classInited;
#endif
#endif
