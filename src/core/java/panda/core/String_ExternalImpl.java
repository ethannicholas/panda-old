package panda.core;

class String_ExternalImpl implements panda.core.String_External {
    @Override
    public float pandaStringToReal32_class_panda$core$String_$Rpanda$core$Real32(panda.core.String s) {
        try {
            return java.lang.Float.parseFloat(PandaCore.toJavaString(s));
        }
        catch (java.lang.NumberFormatException e) {
            return Float.NaN;
        }
    }

    @Override
    public double pandaStringToReal64_class_panda$core$String_$Rpanda$core$Real64(panda.core.String s) {
        try {
            return java.lang.Double.parseDouble(PandaCore.toJavaString(s));
        }
        catch (java.lang.NumberFormatException e) {
            return Double.NaN;
        }
    }
}
