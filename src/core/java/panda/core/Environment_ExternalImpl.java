package panda.core;

class Environment_ExternalImpl implements panda.core.Environment_External {
    @Override
    public panda.core.String pandaGetEnv(panda.core.String key) {
        java.lang.String raw = java.lang.System.getenv(PandaCore.toJavaString(key));
        return raw != null ? PandaCore.newString(raw) : null;
    }
}
