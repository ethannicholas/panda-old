package panda.core;

class Object_ExternalImpl implements panda.core.Object_External {
    @Override
    public int hash(panda.core.Object o) {
        return java.lang.System.identityHashCode(o);
    }
}
