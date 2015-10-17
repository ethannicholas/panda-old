package panda.core;

class Real64Wrapper_ExternalImpl implements panda.core.Real64Wrapper_External {
    @Override
    public boolean isInfinite_$Rpanda$core$Bit(double self) {
        return Double.isInfinite(self);
    }

    @Override
    public boolean isNaN_$Rpanda$core$Bit(double self) {
        return Double.isNaN(self);
    }

    @Override
    public double sqrt_$Rpanda$core$Real64(double self) {
        return Math.sqrt(self);
    }

    @Override
    public double sin_$Rpanda$core$Real64(double self) {
        return Math.sin(self);
    }

    @Override
    public double cos_$Rpanda$core$Real64(double self) {
        return Math.cos(self);
    }

    @Override
    public double atan2_class_Real64_Real64_$Rpanda$core$Real64(double y, double x) {
        return java.lang.Math.atan2(y, x);
    }
}
