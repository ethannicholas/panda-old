// This file was automatically generated by the Panda compiler
#ifndef MersenneTwister_H
#define MersenneTwister_H
extern panda$core$Class MersenneTwister_class;
#ifndef CLASS_MersenneTwister
#define CLASS_MersenneTwister
struct MersenneTwister {
    panda$core$Class* cl;
    panda$collections$Array$LTpanda$core$UInt32$GT* mt;
    Int64 index;
};

#define MersenneTwister$int32_$Rpanda$core$Int32_INDEX 6
typedef Int32(MersenneTwister$int32_$Rpanda$core$Int32_TYPE)(MersenneTwister* self);
#define MersenneTwister$int64_$Rpanda$core$Int64_INDEX 8
typedef Int64(MersenneTwister$int64_$Rpanda$core$Int64_TYPE)(MersenneTwister* self);
void MersenneTwister$init(MersenneTwister* self);
MersenneTwister* new_MersenneTwister$init();
void MersenneTwister$init_panda$math$Random(MersenneTwister* self, panda$math$Random*);
MersenneTwister* new_MersenneTwister$init_panda$math$Random(panda$math$Random*);
void MersenneTwister$init_panda$collections$Array$LTpanda$core$UInt32$GT(MersenneTwister* self, panda$collections$Array$LTpanda$core$UInt32$GT*);
MersenneTwister* new_MersenneTwister$init_panda$collections$Array$LTpanda$core$UInt32$GT(panda$collections$Array$LTpanda$core$UInt32$GT*);
void MersenneTwister$init_Int64(MersenneTwister* self, Int64);
MersenneTwister* new_MersenneTwister$init_Int64(Int64);
panda$collections$ListView$LTpanda$core$UInt32$GT* MersenneTwister$get_state_$Rpanda$collections$ListView$LTpanda$core$UInt32$GT(MersenneTwister* self);
UInt32 MersenneTwister$extract_$Rpanda$core$UInt32(MersenneTwister* self);
void MersenneTwister$twist(MersenneTwister* self);
void MersenneTwister$$classInit_class();
extern Int64 class_MersenneTwister$N;
extern Int32 class_MersenneTwister$M;
extern Int32 class_MersenneTwister$W;
extern Int32 class_MersenneTwister$F;
extern Bit class_MersenneTwister$$classInited;
#endif
#endif