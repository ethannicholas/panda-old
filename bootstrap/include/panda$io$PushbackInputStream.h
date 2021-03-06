// This file was automatically generated by the Panda compiler
#ifndef panda$io$PushbackInputStream_H
#define panda$io$PushbackInputStream_H
extern panda$core$Class panda$io$PushbackInputStream_class;
#ifndef CLASS_panda$io$PushbackInputStream
#define CLASS_panda$io$PushbackInputStream
struct panda$io$PushbackInputStream {
    panda$core$Class* cl;
    Bit closed;
    panda$io$InputStream* raw;
    Bit closeUnderlyingStream;
    panda$collections$Array$LTpanda$core$UInt8$GT* pushbackBuffer;
};

#define panda$io$PushbackInputStream$read_$Rpanda$core$UInt8Wrapper$Z_INDEX 9
typedef panda$core$UInt8Wrapper*(panda$io$PushbackInputStream$read_$Rpanda$core$UInt8Wrapper$Z_TYPE)(panda$io$PushbackInputStream* self);
#define panda$io$PushbackInputStream$read_panda$collections$ListWriter$LTpanda$core$UInt8$GT_Int64_$Rpanda$core$Int64Wrapper$Z_INDEX 10
typedef panda$core$Int64Wrapper*(panda$io$PushbackInputStream$read_panda$collections$ListWriter$LTpanda$core$UInt8$GT_Int64_$Rpanda$core$Int64Wrapper$Z_TYPE)(panda$io$PushbackInputStream* self, panda$collections$ListWriter$LTpanda$core$UInt8$GT*, Int64);
#define panda$io$PushbackInputStream$pushback_UInt8_INDEX 15
typedef void(panda$io$PushbackInputStream$pushback_UInt8_TYPE)(panda$io$PushbackInputStream* self, UInt8);
#define panda$io$PushbackInputStream$pushback_panda$collections$ListView$LTpanda$core$UInt8$GT_INDEX 16
typedef void(panda$io$PushbackInputStream$pushback_panda$collections$ListView$LTpanda$core$UInt8$GT_TYPE)(panda$io$PushbackInputStream* self, panda$collections$ListView$LTpanda$core$UInt8$GT*);
#define panda$io$PushbackInputStream$pushback_Char_INDEX 17
typedef void(panda$io$PushbackInputStream$pushback_Char_TYPE)(panda$io$PushbackInputStream* self, Char);
#define panda$io$PushbackInputStream$pushback_panda$collections$ListView$LTpanda$core$Char$GT_INDEX 18
typedef void(panda$io$PushbackInputStream$pushback_panda$collections$ListView$LTpanda$core$Char$GT_TYPE)(panda$io$PushbackInputStream* self, panda$collections$ListView$LTpanda$core$Char$GT*);
void panda$io$PushbackInputStream$init_panda$io$InputStream(panda$io$PushbackInputStream* self, panda$io$InputStream*);
panda$io$PushbackInputStream* new_panda$io$PushbackInputStream$init_panda$io$InputStream(panda$io$InputStream*);
#endif
#endif
