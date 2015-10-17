package panda.core;

class Panda_ExternalImpl implements panda.core.Panda_External {
    @Override
    public long currentTime_class_$Rpanda$core$Int64() {
        return java.lang.System.currentTimeMillis();
    }

    @Override
    public float pow_class_Real32_Int32_$Rpanda$core$Real32(float a, int b) {
        return (float) java.lang.Math.pow(a, b);
    }

    @Override
    public float pow_class_Real32_Real32_$Rpanda$core$Real32(float a, float b) {
        return (float) java.lang.Math.pow(a, b);
    }

    @Override
    public double pow_class_Real64_Int32_$Rpanda$core$Real64(double a, int b) {
        return java.lang.Math.pow(a, b);
    }

    @Override
    public double pow_class_Real64_Real64_$Rpanda$core$Real64(double a, double b) {
        return java.lang.Math.pow(a, b);
    }

    @Override
    public void debugWrite_class_Int32(int i) {
        java.lang.System.out.println(i);
    }

    @Override
    public void debugWrite_class_panda$core$Object(panda.core.Object o) {
        java.lang.System.out.println(o);
    }

    @Override
    public void debugWritePointer_class_panda$core$Object(panda.core.Object o) {
        java.lang.System.out.println(o);
    }

    @Override
    public int allocThreadLocal_class_$Rpanda$core$Int32() {
        return 0;
    }

    @Override
    public panda.collections.HashMap$.$Lpanda$core$Int32$.$Cpanda$core$Object$Z$R getThreadLocals_class_panda$threads$Thread_$Rpanda$collections$HashMap$LTpanda$core$Int32$Cpanda$core$Object$Z$GT(panda.threads.Thread t) {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean instanceOf_class_panda$core$Object$Z_panda$core$Class_Bit_$Rpanda$core$Bit(panda.core.Object o, panda.core.Class c, boolean nullable) {
        if (o == null)
            return nullable;
        return instanceOf(o.$cl, c);
    }

    private boolean instanceOf(panda.core.Class o, panda.core.Class c) {
        while (o != null) {
            if (o == c)
                return true;
            panda.core.Class[] interfaces = PandaCore.interfaces.get(o);
            if (interfaces != null) {
                for (panda.core.Class intf : interfaces) {
                    if (instanceOf(intf, c))
                        return true;
                }
            }
            o = o.$superclass;
        }
        return false;
    }

    @Override
    public int real32Bits_class_Real32_$Rpanda$core$Int32(float r) {
        return java.lang.Float.floatToRawIntBits(r);
    }

    @Override
    public long real64Bits_class_Real64_$Rpanda$core$Int64(double r) {
        return java.lang.Double.doubleToRawLongBits(r);
    }

    @Override
    public boolean callBitFunction_class_panda$core$$NativePointer_$Rpanda$core$Bit(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public byte callInt8Function_class_panda$core$$NativePointer_$Rpanda$core$Int8(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public short callInt16Function_class_panda$core$$NativePointer_$Rpanda$core$Int16(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public int callInt32Function_class_panda$core$$NativePointer_$Rpanda$core$Int32(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public long callInt64Function_class_panda$core$$NativePointer_$Rpanda$core$Int64(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public char callCharFunction_class_panda$core$$NativePointer_$Rpanda$core$Char(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public float callReal32Function_class_panda$core$$NativePointer_$Rpanda$core$Real32(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public double callReal64Function_class_panda$core$$NativePointer_$Rpanda$core$Real64(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public panda.core.Object callObjectFunction_class_panda$core$$NativePointer_$Rpanda$core$Object$Z(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void debugAllocations_class() {
        throw new UnsupportedOperationException();
    }
}
