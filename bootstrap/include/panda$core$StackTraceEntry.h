// This file was automatically generated by the Panda compiler
#ifndef panda$core$StackTraceEntry_H
#define panda$core$StackTraceEntry_H
extern panda$core$Class panda$core$StackTraceEntry_class;
#ifndef CLASS_panda$core$StackTraceEntry
#define CLASS_panda$core$StackTraceEntry
struct panda$core$StackTraceEntry {
    panda$core$Class* cl;
    panda$core$String* fileName;
    panda$core$String* className;
    panda$core$String* methodName;
    Int64 line;
};

#define panda$core$StackTraceEntry$convert_$Rpanda$core$String_INDEX 1
typedef panda$core$String*(panda$core$StackTraceEntry$convert_$Rpanda$core$String_TYPE)(panda$core$StackTraceEntry* self);
void panda$core$StackTraceEntry$init(panda$core$StackTraceEntry* self);
panda$core$StackTraceEntry* new_panda$core$StackTraceEntry$init();
#endif
#endif
