// This file was automatically generated by the Panda compiler
#ifndef panda$collections$PrimitiveArray_H
#define panda$collections$PrimitiveArray_H
extern panda$core$Class panda$collections$PrimitiveArray_class;
#ifndef CLASS_panda$collections$PrimitiveArray
#define CLASS_panda$collections$PrimitiveArray
struct panda$collections$PrimitiveArray {
    panda$core$Class* cl;
    Int64 length;
    void* contents;
};

void panda$collections$PrimitiveArray$setLength_class_panda$core$Object_Int64_Bit_Int64(panda$core$Object*, Int64, Bit, Int64);
void panda$collections$PrimitiveArray$init(panda$collections$PrimitiveArray* self);
panda$collections$PrimitiveArray* new_panda$collections$PrimitiveArray$init();
#endif
#endif
