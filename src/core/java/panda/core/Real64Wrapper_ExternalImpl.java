package panda.core;

class Real64Wrapper_ExternalImpl implements panda.core.Real64Wrapper_External {
    @Override
    public boolean isInfinite(double self) {
        return Double.isInfinite(self);
    }

    @Override
    public boolean isNaN(double self) {
        return Double.isNaN(self);
    }

    @Override
    public double sqrt(double self) {
        return Math.sqrt(self);
    }

    @Override
    public double sin(double self) {
        return Math.sin(self);
    }

    @Override
    public double cos(double self) {
        return Math.cos(self);
    }

    @Override
    public double atan2(double y, double x) {
        return java.lang.Math.atan2(y, x);
    }
}
