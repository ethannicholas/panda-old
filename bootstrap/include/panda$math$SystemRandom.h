// This file was automatically generated by the Panda compiler
#ifndef panda$math$SystemRandom_H
#define panda$math$SystemRandom_H
extern panda$core$Class panda$math$SystemRandom_class;
#ifndef CLASS_panda$math$SystemRandom
#define CLASS_panda$math$SystemRandom
struct panda$math$SystemRandom {
    panda$core$Class* cl;
    panda$io$InputStream* stream;
    panda$math$Random* fallback;
};

#define panda$math$SystemRandom$int32_$Rpanda$core$Int32_INDEX 6
typedef Int32(panda$math$SystemRandom$int32_$Rpanda$core$Int32_TYPE)(panda$math$SystemRandom* self);
#define panda$math$SystemRandom$int64_$Rpanda$core$Int64_INDEX 8
typedef Int64(panda$math$SystemRandom$int64_$Rpanda$core$Int64_TYPE)(panda$math$SystemRandom* self);
void panda$math$SystemRandom$init(panda$math$SystemRandom* self);
panda$math$SystemRandom* new_panda$math$SystemRandom$init();
#endif
#endif