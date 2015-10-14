package panda.io;

class FileInputStream_ExternalImpl implements panda.io.FileInputStream_External {
    @Override
    public java.lang.Object open(panda.core.String path, boolean read, boolean write) {
        try {
            return new java.io.FileInputStream(
                    panda.core.PandaCore.toJavaString(path));
        }
        catch (java.io.IOException e) {
            throw new panda.core.PandaException(
                panda.io.FileNotFoundException.createnew$init(path));
        }
    }

    @Override
    public int close(java.lang.Object nativeFile) {
        try {
            ((java.io.FileInputStream) nativeFile).close();
            return 0;
        }
        catch (java.io.IOException e) {
            throw new panda.core.PandaException(
                    panda.io.IOException.createnew$init(
                        panda.core.PandaCore.newString(e.getMessage())));
        }
    }

    @Override
    public short readInt8(java.lang.Object nativeFile) {
        try {
            return (short) ((java.io.FileInputStream) nativeFile).read();
        }
        catch (java.io.IOException e) {
            throw new panda.core.PandaException(
                    panda.io.IOException.createnew$init(
                        panda.core.PandaCore.newString(e.getMessage())));
        }
    }

    @Override
    public panda.core.Int32Wrapper read(panda.io.FileInputStream in, panda.collections.ListWriter$.$Lpanda$core$Int8$R dest, int max) {
        try {
            byte[] buffer = new byte[max];
            int result = ((java.io.InputStream) in.$nativeFile).read(buffer);
            if (result <= 0)
                return null;
            for (int i = 0; i < result; i++)
                dest.add(buffer[i]);
            return panda.core.Int32Wrapper.createnew$init(result);
        }
        catch (java.io.IOException e) {
            throw new java.lang.RuntimeException(e);
        }
    }

    @Override
    public panda.core.Int32Wrapper read(panda.io.FileInputStream in, panda.collections.ListWriter$.$Lpanda$core$UInt8$R dest, int max) {
        try {
            byte[] buffer = new byte[max];
            int result = ((java.io.InputStream) in.$nativeFile).read(buffer);
            if (result <= 0)
                return null;
            for (int i = 0; i < result; i++)
                dest.add_UInt8(buffer[i]);
            return panda.core.Int32Wrapper.createnew$init(result);
        }
        catch (java.io.IOException e) {
            throw new java.lang.RuntimeException(e);
        }
    }

    @Override
    public panda.core.Int32Wrapper read(panda.io.FileInputStream in, panda.collections.ListWriter$.$Lpanda$core$Char$R dest, int max) {
        try {
            byte[] buffer = new byte[max];
            int result = ((java.io.InputStream) in.$nativeFile).read(buffer);
            if (result <= 0)
                return null;
            for (int i = 0; i < result; i++)
                dest.add((char) buffer[i]);
            return panda.core.Int32Wrapper.createnew$init(result);
        }
        catch (java.io.IOException e) {
            throw new java.lang.RuntimeException(e);
        }
    }
}
