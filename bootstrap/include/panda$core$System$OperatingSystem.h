// This file was automatically generated by the Panda compiler
#ifndef panda$core$System$OperatingSystem_H
#define panda$core$System$OperatingSystem_H
extern panda$core$Class panda$core$System$OperatingSystem_class;
#ifndef CLASS_panda$core$System$OperatingSystem
#define CLASS_panda$core$System$OperatingSystem
struct panda$core$System$OperatingSystem {
    panda$core$Class* cl;
};

#define panda$core$System$OperatingSystem$convert_$Rpanda$core$String_INDEX 1
typedef panda$core$String*(panda$core$System$OperatingSystem$convert_$Rpanda$core$String_TYPE)(panda$core$System$OperatingSystem* self);
#define panda$core$System$OperatingSystem$convert_$Rpanda$core$Int64_INDEX 4
typedef Int64(panda$core$System$OperatingSystem$convert_$Rpanda$core$Int64_TYPE)(panda$core$System$OperatingSystem* self);
void panda$core$System$OperatingSystem$$classInit_class();
void panda$core$System$OperatingSystem$init(panda$core$System$OperatingSystem* self);
panda$core$System$OperatingSystem* new_panda$core$System$OperatingSystem$init();
panda$core$System$OperatingSystem* panda$core$System$OperatingSystem$fromInt_class_Int64_$Rpanda$core$System$OperatingSystem(Int64);
panda$core$System$OperatingSystem* panda$core$System$OperatingSystem$fromString_class_panda$core$String_$Rpanda$core$System$OperatingSystem(panda$core$String*);
extern panda$core$System$OperatingSystem* class_panda$core$System$OperatingSystem$MACOSX;
extern panda$core$System$OperatingSystem* class_panda$core$System$OperatingSystem$LINUX;
extern panda$core$System$OperatingSystem* class_panda$core$System$OperatingSystem$OTHER_UNIX;
extern panda$core$System$OperatingSystem* class_panda$core$System$OperatingSystem$WINDOWS;
extern panda$core$System$OperatingSystem* class_panda$core$System$OperatingSystem$UNKNOWN;
extern Bit class_panda$core$System$OperatingSystem$$classInited;
#endif
#endif
