package panda.core;

class Real32Wrapper_ExternalImpl implements panda.core.Real32Wrapper_External {
    @Override
    public panda.core.String pandaReal32ToString_class_Real32_$Rpanda$core$String(float r) {
        java.lang.String result = java.lang.String.valueOf(r);
        if (result.endsWith(".0"))
            result = result.substring(0, result.length() - 2);
        return PandaCore.newString(result);
    }

    @Override
    public boolean isInfinite_$Rpanda$core$Bit(float self) {
        return Float.isInfinite(self);
    }

    @Override
    public boolean isNaN_$Rpanda$core$Bit(float self) {
        return Float.isNaN(self);
    }

    @Override
    public float sqrt_$Rpanda$core$Real32(float self) {
        return (float) Math.sqrt(self);
    }

    @Override
    public float sin_$Rpanda$core$Real32(float self) {
        return (float) Math.sin(self);
    }

    @Override
    public float cos_$Rpanda$core$Real32(float self) {
        return (float) Math.cos(self);
    }
}
