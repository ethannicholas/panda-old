package panda.core;

class Object_ExternalImpl implements panda.core.Object_External {
    @Override
    public int get_hash_$Rpanda$core$Int32(panda.core.Object o) {
        return java.lang.System.identityHashCode(o);
    }
}
