package panda.core;

class Matcher_ExternalImpl implements panda.core.Matcher_External {
    @Override
    public void setText_class_panda$core$$NativePointer_panda$core$String(java.lang.Object nativeHandle, panda.core.String text) {
        ((java.util.regex.Matcher) nativeHandle).reset(
                panda.core.PandaCore.toJavaString(text));
    }

    @Override
    public boolean matches_class_panda$core$$NativePointer_$Rpanda$core$Bit(java.lang.Object nativeHandle) {
        return ((java.util.regex.Matcher) nativeHandle).matches();
    }

    @Override
    public boolean find_class_panda$core$$NativePointer_Int64_$Rpanda$core$Bit(java.lang.Object nativeHandle, long startIndex) {
        return ((java.util.regex.Matcher) nativeHandle).find((int) startIndex);
    }

    @Override
    public panda.core.String group_class_panda$core$$NativePointer_Int64_$Rpanda$core$String(java.lang.Object nativeHandle, long group) {
        java.lang.String raw = ((java.util.regex.Matcher) nativeHandle).group((int) group);
        return panda.core.PandaCore.newString(raw != null ? raw : "");
    }

    @Override
    public long _groupCount_class_panda$core$$NativePointer_$Rpanda$core$Int64(java.lang.Object nativeHandle) {
        return ((java.util.regex.Matcher) nativeHandle).groupCount() + 1;
    }

    @Override
    public long _start_class_panda$core$$NativePointer_$Rpanda$core$Int64(java.lang.Object nativeHandle) {
        return ((java.util.regex.Matcher) nativeHandle).start();
    }

    @Override
    public long _end_class_panda$core$$NativePointer_$Rpanda$core$Int64(java.lang.Object nativeHandle) {
        return ((java.util.regex.Matcher) nativeHandle).end();
    }
}