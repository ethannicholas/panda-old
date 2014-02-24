package panda.io;

class FileInputStream_ExternalImpl implements panda.io.FileInputStream_External {
    @Override
    public int read(panda.io.FileInputStream self, panda.collections.Array$LTInt8$GT b, int offset, int length) {
        throw new UnsupportedOperationException();
    }

    @Override
    public java.lang.Object open(panda.core.String path, boolean read, boolean write) {
        try {
            return new java.io.FileInputStream(
                    panda.core.PandaCore.toJavaString(path));
        }
        catch (java.io.IOException e) {
            throw new panda.core.PandaException(
                panda.io.FileNotFoundException.createnew$constructor(path));
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
                    panda.io.IOException.createnew$constructor(
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
                    panda.io.IOException.createnew$constructor(
                        panda.core.PandaCore.newString(e.getMessage())));
        }
    }
}
