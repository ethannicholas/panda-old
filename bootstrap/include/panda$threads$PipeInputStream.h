// This file was automatically generated by the Panda compiler
#ifndef panda$threads$PipeInputStream_H
#define panda$threads$PipeInputStream_H
extern panda$core$Class panda$threads$PipeInputStream_class;
#ifndef CLASS_panda$threads$PipeInputStream
#define CLASS_panda$threads$PipeInputStream
struct panda$threads$PipeInputStream {
    panda$core$Class* cl;
    Bit closed;
    panda$threads$MessageQueue* queue;
    Int64 bufferIndex;
    panda$collections$ImmutableArray$LTpanda$core$UInt8$GT* buffer;
};

#define panda$threads$PipeInputStream$read_$Rpanda$core$UInt8Wrapper$Z_INDEX 9
typedef panda$core$UInt8Wrapper*(panda$threads$PipeInputStream$read_$Rpanda$core$UInt8Wrapper$Z_TYPE)(panda$threads$PipeInputStream* self);
void panda$threads$PipeInputStream$init_panda$threads$MessageQueue$LTpanda$collections$ImmutableArray$LTpanda$core$UInt8$GT$Z$GT(panda$threads$PipeInputStream* self, panda$threads$MessageQueue*);
panda$threads$PipeInputStream* new_panda$threads$PipeInputStream$init_panda$threads$MessageQueue$LTpanda$collections$ImmutableArray$LTpanda$core$UInt8$GT$Z$GT(panda$threads$MessageQueue*);
#endif
#endif