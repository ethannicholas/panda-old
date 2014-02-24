package panda.io;

class Console_ExternalImpl implements panda.io.Console_External {
    @Override
    public java.lang.Object stdIn() {
        return new java.io.FileInputStream(java.io.FileDescriptor.in);
    }

    @Override
    public java.lang.Object stdOut() {
        return new java.io.FileOutputStream(java.io.FileDescriptor.out);
    }
}
