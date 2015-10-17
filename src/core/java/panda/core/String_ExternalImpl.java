package panda.core;

class String_ExternalImpl implements panda.core.String_External {
    @Override
    public panda.core.String pandaReal32ToString_class_Real32_$Rpanda$core$String(float r) {
        java.lang.String result = java.lang.String.valueOf(r);
        if (result.endsWith(".0"))
            result = result.substring(0, result.length() - 2);
        return PandaCore.newString(result);
    }

    @Override
    public panda.core.String pandaReal64ToString_class_Real64_$Rpanda$core$String(double r) {
        java.lang.String result = java.lang.String.valueOf(r);
        if (result.endsWith(".0"))
            result = result.substring(0, result.length() - 2);
        return PandaCore.newString(result);
    }

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
