// This file was automatically generated by the Panda compiler
#ifndef panda$threads$Message_H
#define panda$threads$Message_H
extern panda$core$Class panda$threads$Message_class;
#ifndef CLASS_panda$threads$Message
#define CLASS_panda$threads$Message
struct panda$threads$Message {
    panda$core$Class* cl;
    panda$core$Object* data;
    panda$threads$Message* prev;
    panda$threads$Message* next;
};

void panda$threads$Message$init_panda$core$Object$Z(panda$threads$Message* self, panda$core$Object*);
panda$threads$Message* new_panda$threads$Message$init_panda$core$Object$Z(panda$core$Object*);
#endif
#endif