package panda.core;

class Object_ExternalImpl implements panda.core.Object_External {
    @Override
    public long get_hash_$Rpanda$core$Int64(panda.core.Object o) {
        return java.lang.System.identityHashCode(o);
    }
}
