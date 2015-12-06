package panda.core;

import panda.collections.PrimitiveArray$.$LChar$R;
import panda.collections.PrimitiveArray$.$Lpanda$core$String$R;
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

    static java.util.Map<panda.core.Class, panda.core.Class[]> interfaces = 
            new java.util.HashMap<panda.core.Class, panda.core.Class[]>();

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

    public static void initClass(panda.core.Class cl,
            panda.core.Class superclass, panda.core.Class[] interfaces) {
        cl.$superclass = superclass;
        PandaCore.interfaces.put(cl, interfaces);
    }

    public static panda.core.String newString(java.lang.String string) {
        panda.collections.PrimitiveArray$.$LChar$R chars = new panda.collections.PrimitiveArray$.$LChar$R();
        chars.$cl = getClass("panda.collections.Array<Char>");
        chars.$$length = string.length();
        chars.contents = string.toCharArray();
        return panda.core.String.createnew$init_panda$collections$PrimitiveArray$LTpanda$core$Char$GT(chars);
    }
    
    public static java.lang.String toJavaString(panda.core.String string) {
        int length = string.get_length_$Rpanda$core$Int32();
        char[] chars = new char[length];
        for (int i = 0; i < length; i++)
            chars[i] = string.$ARR_Int32_$Rpanda$core$Char(i);
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
        throw new panda.core.PandaException(panda.core.CastError.createnew$init_panda$core$String(
                newString(value + " is not an instance of " + dest)));
    }

    public static <T> T checkCastNullable(T value, java.lang.Class dest) {
        if (value == null || dest.isInstance(value))
            return value;
        throw new panda.core.PandaException(panda.core.CastError.createnew$init_panda$core$String(
                newString(value + " is not an instance of " + dest)));
    }

    public static panda.collections.Array$.$Lpanda$core$String$R convertArgs(java.lang.String[] arg) {
        panda.collections.PrimitiveArray$.$Lpanda$core$String$R result = 
                new panda.collections.PrimitiveArray$.$Lpanda$core$String$R();
        result.$$length = arg.length;
        panda.core.String[] contents = new panda.core.String[arg.length];
        for (int i = 0; i < arg.length; i++)
            contents[i] = newString(arg[i]);
        result.contents = contents;
        return panda.collections.Array$.$Lpanda$core$String$R.createnew$init_panda$collections$PrimitiveArray$LTpanda$core$String$GT(result);
    }

    public static java.lang.Object skip(java.lang.Object a, java.lang.Object b) {
        return b;
    }
}