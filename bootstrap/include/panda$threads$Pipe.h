// This file was automatically generated by the Panda compiler
#ifndef panda$threads$Pipe_H
#define panda$threads$Pipe_H
extern panda$core$Class panda$threads$Pipe_class;
#ifndef CLASS_panda$threads$Pipe
#define CLASS_panda$threads$Pipe
struct panda$threads$Pipe {
    panda$core$Class* cl;
    panda$threads$MessageQueue* queue;
};

#define panda$threads$Pipe$openOutputStream_$Rpanda$io$OutputStream_INDEX 4
typedef panda$io$OutputStream*(panda$threads$Pipe$openOutputStream_$Rpanda$io$OutputStream_TYPE)(panda$threads$Pipe* self);
#define panda$threads$Pipe$openInputStream_$Rpanda$io$InputStream_INDEX 5
typedef panda$io$InputStream*(panda$threads$Pipe$openInputStream_$Rpanda$io$InputStream_TYPE)(panda$threads$Pipe* self);
void panda$threads$Pipe$init(panda$threads$Pipe* self);
panda$threads$Pipe* new_panda$threads$Pipe$init();
#endif
#endif