package panda.core;

import panda.collections.PrimitiveArray$LTChar$GT;
import panda.collections.PrimitiveArray$LTpanda$core$String$GT;
import panda.core.Class;

/**
 * General utility methods which the Panda->Java compiler uses to implement
 * some core features.
 */
public class PandaCore {
    private static java.math.BigInteger two64 = 
            new java.math.BigInteger("18446744073709551616");

    private static java.util.Map<java.lang.String, panda.core.Class> classes = 
            new java.util.HashMap<java.lang.String, panda.core.Class>();

    public static synchronized panda.core.Class getClass(
            java.lang.String name) {
        return getClass(name, name);
    }
    
    public static synchronized panda.core.Class getClass(
            java.lang.String name, java.lang.String displayName) {
        panda.core.Class result = classes.get(name);
        if (result == null) {
            result = new panda.core.Class();
            classes.put(name, result);
            result.$name = newString(displayName);
        }
        return result;
    }

    public static void initClass(panda.core.Class cl,
            panda.core.Class superclass) {
        cl.$superclass = superclass;
    }

    public static panda.core.String newString(java.lang.String string) {
        PrimitiveArray$LTChar$GT chars = new PrimitiveArray$LTChar$GT();
        chars.$cl = getClass("panda.collections.Array<Char>");
        chars.$$length = string.length();
        chars.contents = string.toCharArray();
        return panda.core.String.createnew$constructor(chars);
    }
    
    public static java.lang.String toJavaString(panda.core.String string) {
        int length = string.length();
        char[] chars = new char[length];
        for (int i = 0; i < length; i++)
            chars[i] = string.$ARR(i);
        return new java.lang.String(chars);
    }

    public static java.math.BigInteger UInt64(long raw) {
        java.math.BigInteger result = java.math.BigInteger.valueOf(raw);
        if (raw < 0)
            result = two64.add(result);
        return result;
    }

    public static <T> T checkCast(T value, java.lang.Class dest) {
        if (dest.isInstance(value))
            return value;
        throw new panda.core.PandaException(panda.core.CastError.createnew$constructor(
                newString(value + " is not an instance of " + dest)));
    }

    public static <T> T checkCastNullable(T value, java.lang.Class dest) {
        if (value == null || dest.isInstance(value))
            return value;
        throw new panda.core.PandaException(panda.core.CastError.createnew$constructor(
                newString(value + " is not an instance of " + dest)));
    }

    public static PrimitiveArray$LTpanda$core$String$GT convertArgs(java.lang.String[] arg) {
        PrimitiveArray$LTpanda$core$String$GT result = new PrimitiveArray$LTpanda$core$String$GT();
        result.$$length = arg.length;
        panda.core.String[] contents = new panda.core.String[arg.length];
        for (int i = 0; i < arg.length; i++)
            contents[i] = newString(arg[i]);
        result.contents = contents;
        return result;
    }
}