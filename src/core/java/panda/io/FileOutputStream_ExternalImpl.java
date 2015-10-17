package panda.io;

class FileOutputStream_ExternalImpl implements panda.io.FileOutputStream_External {
    @Override
    public java.lang.Object open_class_panda$core$String_Bit_Bit_$Rpanda$core$$NativePointer(panda.core.String path, boolean read, boolean write) {
        try {
            return new java.io.FileOutputStream(
                    panda.core.PandaCore.toJavaString(path));
        }
        catch (java.io.IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public int close_class_panda$core$$NativePointer_$Rpanda$core$Int32(java.lang.Object nativeFile) {
        try {
            ((java.io.FileOutputStream) nativeFile).close();
            return 0;
        }
        catch (java.io.IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void writeInt8_class_panda$core$$NativePointer_Int8(java.lang.Object nativeFile, byte b) {
        try {
            ((java.io.FileOutputStream) nativeFile).write(b);
        }
        catch (java.io.IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void writeInt8Array_class_panda$core$$NativePointer_panda$collections$ListView$LTpanda$core$Int8$GT_Int32_Int32(java.lang.Object nativeFile, panda.collections.ListView$.$Lpanda$core$Int8$R b, int offset, int length) {
        try {
            byte[] buffer = new byte[length];
            for (int i = 0; i < length; i++)
                buffer[i] = b.$ARR_Int32_$Rpanda$core$Int8(i + offset);
            ((java.io.FileOutputStream) nativeFile).write(buffer);
        }
        catch (java.io.IOException e) {
            throw new RuntimeException(e);
        }
    }
}
