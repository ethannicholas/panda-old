package panda.core;

class Real64Wrapper_ExternalImpl implements panda.core.Real64Wrapper_External {
    @Override
    public panda.core.String pandaReal64ToString_class_Real64_$Rpanda$core$String(double r) {
        java.lang.String result = java.lang.String.valueOf(r);
        if (result.endsWith(".0"))
            result = result.substring(0, result.length() - 2);
        return PandaCore.newString(result);
    }

    @Override
    public boolean get_isInfinite_$Rpanda$core$Bit(double self) {
        return Double.isInfinite(self);
    }

    @Override
    public boolean get_isNaN_$Rpanda$core$Bit(double self) {
        return Double.isNaN(self);
    }

    @Override
    public double get_sqrt_$Rpanda$core$Real64(double self) {
        return Math.sqrt(self);
    }

    @Override
    public double get_sin_$Rpanda$core$Real64(double self) {
        return Math.sin(self);
    }

    @Override
    public double get_cos_$Rpanda$core$Real64(double self) {
        return Math.cos(self);
    }

    @Override
    public double atan2_class_Real64_Real64_$Rpanda$core$Real64(double y, double x) {
        return java.lang.Math.atan2(y, x);
    }
}
