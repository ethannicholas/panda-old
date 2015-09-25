package panda.core;

class Error_ExternalImpl implements panda.core.Error_External {
    @Override
    public panda.collections.ImmutablePrimitiveArray$.$Lpanda$core$StackTraceEntry$R 
            getStackTrace(panda.core.Error self) {
        panda.collections.ImmutablePrimitiveArray$.$Lpanda$core$StackTraceEntry$R result =
                new panda.collections.ImmutablePrimitiveArray$.$Lpanda$core$StackTraceEntry$R();
        java.lang.StackTraceElement[] trace = 
                new java.lang.Throwable().getStackTrace();
        result.contents = new panda.core.StackTraceEntry[trace.length];
        result.$$length = trace.length;
        result.$$maxLength = trace.length;
        for (int i = 0; i < trace.length; i++) {
            java.lang.StackTraceElement javaEntry = trace[i];
            panda.core.StackTraceEntry entry = new panda.core.StackTraceEntry();
            entry.$fileName = panda.core.PandaCore.newString(javaEntry.getFileName());
            entry.$className = panda.core.PandaCore.newString(javaEntry.getClassName());
            entry.$methodName = panda.core.PandaCore.newString(javaEntry.getMethodName());
            entry.$line = javaEntry.getLineNumber();
            result.contents[i] = entry;
        }
        return result;
    }
}
