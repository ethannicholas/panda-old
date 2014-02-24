package panda.core;

class String_ExternalImpl implements panda.core.String_External {
    @Override
    public panda.core.String pandaReal32ToString(float r) {
        java.lang.String result = java.lang.String.valueOf(r);
        if (result.endsWith(".0"))
            result = result.substring(0, result.length() - 2);
        return PandaCore.newString(result);
    }

    @Override
    public panda.core.String pandaReal64ToString(double r) {
        java.lang.String result = java.lang.String.valueOf(r);
        if (result.endsWith(".0"))
            result = result.substring(0, result.length() - 2);
        return PandaCore.newString(result);
    }

    @Override
    public float pandaStringToReal32(panda.core.String s) {
        try {
            return java.lang.Float.parseFloat(PandaCore.toJavaString(s));
        }
        catch (java.lang.NumberFormatException e) {
            return Float.NaN;
        }
    }

    @Override
    public double pandaStringToReal64(panda.core.String s) {
        try {
            return java.lang.Double.parseDouble(PandaCore.toJavaString(s));
        }
        catch (java.lang.NumberFormatException e) {
            return Double.NaN;
        }
    }
}
