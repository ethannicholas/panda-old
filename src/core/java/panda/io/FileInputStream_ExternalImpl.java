package panda.io;

class FileInputStream_ExternalImpl implements panda.io.FileInputStream_External {
    @Override
    public java.lang.Object open_class_panda$core$String_Bit_Bit_$Rpanda$core$$NativePointer(panda.core.String path, boolean read, boolean write) {
        try {
            return new java.io.FileInputStream(
                    panda.core.PandaCore.toJavaString(path));
        }
        catch (java.io.IOException e) {
            throw new panda.core.PandaException(
                panda.io.FileNotFoundException.createnew$init_panda$core$String(path));
        }
    }

    @Override
    public long close_class_panda$core$$NativePointer_$Rpanda$core$Int64(java.lang.Object nativeFile) {
        try {
            ((java.io.FileInputStream) nativeFile).close();
            return 0;
        }
        catch (java.io.IOException e) {
            throw new panda.core.PandaException(
                    panda.io.IOException.createnew$init_panda$core$String(
                        panda.core.PandaCore.newString(e.getMessage())));
        }
    }

    @Override
    public short read_class_panda$core$$NativePointer_$Rpanda$core$Int16(java.lang.Object nativeFile) {
        try {
            return (short) ((java.io.FileInputStream) nativeFile).read();
        }
        catch (java.io.IOException e) {
            throw new panda.core.PandaException(
                    panda.io.IOException.createnew$init_panda$core$String(
                        panda.core.PandaCore.newString(e.getMessage())));
        }
    }

    @Override
    public panda.core.Int64Wrapper read_panda$collections$ListWriter$LTpanda$core$UInt8$GT_Int64_$Rpanda$core$Int64Wrapper$Z(panda.io.FileInputStream in, panda.collections.ListWriter$.$Lpanda$core$UInt8$R dest, long max) {
        try {
            byte[] buffer = new byte[(int) max];
            int result = ((java.io.InputStream) in.$nativeFile).read(buffer);
            if (result <= 0)
                return null;
            for (int i = 0; i < result; i++)
                dest.add_UInt8(buffer[i]);
            return panda.core.Int64Wrapper.createnew$init_Int64(result);
        }
        catch (java.io.IOException e) {
            throw new java.lang.RuntimeException(e);
        }
    }
}
