package panda.core;

class Real32Wrapper_ExternalImpl implements panda.core.Real32Wrapper_External {
    @Override
    public boolean isInfinite(float self) {
        return Float.isInfinite(self);
    }

    @Override
    public boolean isNaN(float self) {
        return Float.isNaN(self);
    }

    @Override
    public float sqrt(float self) {
        return (float) Math.sqrt(self);
    }

    @Override
    public float sin(float self) {
        return (float) Math.sin(self);
    }

    @Override
    public float cos(float self) {
        return (float) Math.cos(self);
    }
}
