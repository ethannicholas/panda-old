package panda.core;

class Matcher_ExternalImpl implements panda.core.Matcher_External {
    @Override
    public void setText(java.lang.Object nativeHandle, panda.core.String text) {
        ((java.util.regex.Matcher) nativeHandle).reset(
                panda.core.PandaCore.toJavaString(text));
    }

    @Override
    public boolean matches(java.lang.Object nativeHandle) {
        return ((java.util.regex.Matcher) nativeHandle).matches();
    }

    @Override
    public boolean find(java.lang.Object nativeHandle, int startIndex) {
        return ((java.util.regex.Matcher) nativeHandle).find(startIndex);
    }

    @Override
    public panda.core.String group(java.lang.Object nativeHandle, int group) {
        java.lang.String raw = ((java.util.regex.Matcher) nativeHandle).group(group);
        return panda.core.PandaCore.newString(raw != null ? raw : "");
    }

    @Override
    public int groupCount(java.lang.Object nativeHandle) {
        return ((java.util.regex.Matcher) nativeHandle).groupCount() + 1;
    }

    @Override
    public int start(java.lang.Object nativeHandle) {
        return ((java.util.regex.Matcher) nativeHandle).start();
    }

    @Override
    public int end(java.lang.Object nativeHandle) {
        return ((java.util.regex.Matcher) nativeHandle).end();
    }
}