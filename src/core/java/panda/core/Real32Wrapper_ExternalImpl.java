package panda.core;

class Real32Wrapper_ExternalImpl implements panda.core.Real32Wrapper_External {
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
