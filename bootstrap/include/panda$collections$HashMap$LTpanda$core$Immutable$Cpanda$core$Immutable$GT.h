// This file was automatically generated by the Panda compiler
#ifndef panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT_H
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT_H
extern panda$core$Class panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT_class;
#ifndef CLASS_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT
#define CLASS_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT
struct panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT {
    panda$core$Class* cl;
    Int64 _length;
    panda$collections$PrimitiveArray$LTpanda$collections$MutableMapEntry$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$Z$GT* contents;
    Int64 threshold;
    Int64 changeCount;
};

#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$convert_$Rpanda$core$String_INDEX 1
typedef panda$core$String*(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$convert_$Rpanda$core$String_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$$EQ_panda$core$Object_$Rpanda$core$Bit_INDEX 2
typedef Bit(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$$EQ_panda$core$Object_$Rpanda$core$Bit_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$core$Object*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$addAll_panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Immutable$GT_INDEX 4
typedef void(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$addAll_panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Immutable$GT_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Immutable$GT*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$remove_panda$core$Immutable_INDEX 5
typedef void(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$remove_panda$core$Immutable_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$core$Immutable*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$$ARREQ_panda$core$Immutable_panda$core$Immutable_INDEX 6
typedef void(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$$ARREQ_panda$core$Immutable_panda$core$Immutable_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$core$Immutable*, panda$core$Immutable*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$clear_INDEX 7
typedef void(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$clear_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$get_iterator_$Rpanda$collections$Iterator$LT$LPpanda$core$Immutable$Cpanda$core$Immutable$RP$GT_INDEX 8
typedef panda$collections$Iterator$LT$LPpanda$core$Immutable$Cpanda$core$Immutable$RP$GT*(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$get_iterator_$Rpanda$collections$Iterator$LT$LPpanda$core$Immutable$Cpanda$core$Immutable$RP$GT_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$get_count_$Rpanda$core$Int64_INDEX 10
typedef Int64(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$get_count_$Rpanda$core$Int64_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$$ARR_panda$core$Immutable_$Rpanda$core$Immutable$Z_INDEX 12
typedef panda$core$Immutable*(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$$ARR_panda$core$Immutable_$Rpanda$core$Immutable$Z_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$core$Immutable*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$contains_panda$core$Immutable_$Rpanda$core$Bit_INDEX 13
typedef Bit(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$contains_panda$core$Immutable_$Rpanda$core$Bit_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$core$Immutable*);
#define panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$get_iterator_$Rpanda$collections$Iterator$LTpanda$core$Object$Z$GT_INDEX 14
typedef panda$collections$Iterator$LTpanda$core$Object$Z$GT*(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$get_iterator_$Rpanda$collections$Iterator$LTpanda$core$Object$Z$GT_TYPE)(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init();
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init_panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT_panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT*, panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT*);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init_panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT_panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT(panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT*, panda$collections$PrimitiveArray$LTpanda$core$Immutable$GT*);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init_panda$collections$ListView$LTpanda$core$Immutable$GT_panda$collections$ListView$LTpanda$core$Immutable$GT(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$collections$ListView$LTpanda$core$Immutable$GT*, panda$collections$ListView$LTpanda$core$Immutable$GT*);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init_panda$collections$ListView$LTpanda$core$Immutable$GT_panda$collections$ListView$LTpanda$core$Immutable$GT(panda$collections$ListView$LTpanda$core$Immutable$GT*, panda$collections$ListView$LTpanda$core$Immutable$GT*);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init_panda$collections$ListView$LT$LPpanda$core$Immutable$Cpanda$core$Immutable$RP$GT(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$collections$ListView$LT$LPpanda$core$Immutable$Cpanda$core$Immutable$RP$GT*);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init_panda$collections$ListView$LT$LPpanda$core$Immutable$Cpanda$core$Immutable$RP$GT(panda$collections$ListView$LT$LPpanda$core$Immutable$Cpanda$core$Immutable$RP$GT*);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init_panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Immutable$GT(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Immutable$GT*);
panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* new_panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$init_panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Immutable$GT(panda$collections$MapView$LTpanda$core$Immutable$Cpanda$core$Immutable$GT*);
Int64 panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$indexFor_panda$core$Immutable_$Rpanda$core$Int64(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self, panda$core$Immutable*);
void panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT$incrementLength(panda$collections$HashMap$LTpanda$core$Immutable$Cpanda$core$Immutable$GT* self);
extern Int64 class_panda$collections$HashMap$DEFAULT_LENGTH;
extern Real64 class_panda$collections$HashMap$LOAD_FACTOR;
extern Bit class_panda$collections$HashMap$$classInited;
#endif
#endif