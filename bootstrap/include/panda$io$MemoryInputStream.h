// This file was automatically generated by the Panda compiler
#ifndef panda$io$MemoryInputStream_H
#define panda$io$MemoryInputStream_H
extern panda$core$Class panda$io$MemoryInputStream_class;
#ifndef CLASS_panda$io$MemoryInputStream
#define CLASS_panda$io$MemoryInputStream
struct panda$io$MemoryInputStream {
    panda$core$Class* cl;
    Bit closed;
    panda$collections$ImmutableArray$LTpanda$core$UInt8$GT* data;
    Int64 index;
};

#define panda$io$MemoryInputStream$read_$Rpanda$core$UInt8Wrapper$Z_INDEX 9
typedef panda$core$UInt8Wrapper*(panda$io$MemoryInputStream$read_$Rpanda$core$UInt8Wrapper$Z_TYPE)(panda$io$MemoryInputStream* self);
void panda$io$MemoryInputStream$init_panda$core$String(panda$io$MemoryInputStream* self, panda$core$String*);
panda$io$MemoryInputStream* new_panda$io$MemoryInputStream$init_panda$core$String(panda$core$String*);
void panda$io$MemoryInputStream$init_panda$collections$Array$LTpanda$core$UInt8$GT(panda$io$MemoryInputStream* self, panda$collections$Array$LTpanda$core$UInt8$GT*);
panda$io$MemoryInputStream* new_panda$io$MemoryInputStream$init_panda$collections$Array$LTpanda$core$UInt8$GT(panda$collections$Array$LTpanda$core$UInt8$GT*);
void panda$io$MemoryInputStream$init_panda$collections$ImmutableArray$LTpanda$core$UInt8$GT(panda$io$MemoryInputStream* self, panda$collections$ImmutableArray$LTpanda$core$UInt8$GT*);
panda$io$MemoryInputStream* new_panda$io$MemoryInputStream$init_panda$collections$ImmutableArray$LTpanda$core$UInt8$GT(panda$collections$ImmutableArray$LTpanda$core$UInt8$GT*);
#endif
#endif
