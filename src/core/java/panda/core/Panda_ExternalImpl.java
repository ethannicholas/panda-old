package panda.core;

class Panda_ExternalImpl implements panda.core.Panda_External {
    @Override
    public long currentTime() {
        return java.lang.System.currentTimeMillis();
    }

    @Override
    public float pow(float a, int b) {
        return (float) java.lang.Math.pow(a, b);
    }

    @Override
    public float pow(float a, float b) {
        return (float) java.lang.Math.pow(a, b);
    }

    @Override
    public double pow(double a, int b) {
        return java.lang.Math.pow(a, b);
    }

    @Override
    public double pow(double a, double b) {
        return java.lang.Math.pow(a, b);
    }

    @Override
    public void debugWrite(int i) {
        java.lang.System.out.println(i);
    }

    @Override
    public void debugWrite(panda.core.Object o) {
        java.lang.System.out.println(o);
    }

    @Override
    public void debugWritePointer(panda.core.Object o) {
        java.lang.System.out.println(o);
    }

    @Override
    public int allocThreadLocal() {
        return 0;
    }

    @Override
    public panda.collections.HashMap$LTpanda$core$Int32$Cpanda$core$Object$GT getThreadLocals(panda.threads.Thread t) {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean instanceOf(panda.core.Object o, panda.core.Class c, boolean nullable) {
        if (o == null)
            return nullable;
        Class oc = o.$cl;
        while (oc != null) {
            if (oc == c)
                return true;
            oc = oc.$superclass;
        }
        return false;
    }

    @Override
    public int real32Bits(float r) {
        return java.lang.Float.floatToRawIntBits(r);
    }

    @Override
    public long real64Bits(double r) {
        return java.lang.Double.doubleToRawLongBits(r);
    }

    @Override
    public boolean callBitFunction(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public byte callInt8Function(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public short callInt16Function(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public int callInt32Function(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public long callInt64Function(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public char callCharFunction(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public float callReal32Function(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public double callReal64Function(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public panda.core.Object callObjectFunction(java.lang.Object f) {
        throw new UnsupportedOperationException();
    }

    @Override
    public void debugAllocations() {
        throw new UnsupportedOperationException();
    }
}
