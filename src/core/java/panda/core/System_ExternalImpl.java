package panda.core;

class System_ExternalImpl implements panda.core.System_External {
    @Override
    public panda.core.OperatingSystemInfo operatingSystem_class_$Rpanda$core$OperatingSystemInfo() {
        java.lang.String os = java.lang.System.getProperty("os.name");
        panda.core.OperatingSystemType type;
        if (os.startsWith("Mac OS"))
            type = panda.core.OperatingSystemType.$MACOSX;
        else
            type = panda.core.OperatingSystemType.$LINUX;
        return panda.core.OperatingSystemInfo.createnew$init_panda$core$OperatingSystemType(type);
    }

    @Override
    public void exit_class_Int32(int exitCode) {
        java.lang.System.exit(exitCode);
    }

    @Override
    public void exec_class_panda$io$File_panda$io$File_panda$collections$ListView$LTpanda$core$String$GT(panda.io.File command, panda.io.File dir, 
            panda.collections.ListView$.$Lpanda$core$String$R args) {
        java.lang.String[] cmd = new java.lang.String[args.length_$Rpanda$core$Int32() + 1];
        cmd[0] = panda.core.PandaCore.toJavaString(command.$path);
        for (int i = 0; i < args.length_$Rpanda$core$Int32(); i++) {
            cmd[i + 1] = panda.core.PandaCore.toJavaString(args.$ARR_Int32_$Rpanda$core$String(i));
        }
        try {
            java.lang.Process p = java.lang.Runtime.getRuntime().exec(cmd, null,
                    new java.io.File(PandaCore.toJavaString(dir.$path)));
            final java.io.InputStream in = p.getInputStream();
            java.lang.Thread thread1 = new java.lang.Thread() {
                public void run() {
                    byte[] buffer = new byte[2048];
                    int c;
                    try {
                        while ((c = in.read(buffer)) > 0)
                            java.lang.System.out.write(buffer, 0, c);
                    } 
                    catch (java.io.IOException e) {
                        throw new java.lang.RuntimeException(e);
                    }
                }
            };
            thread1.start();
            final java.io.InputStream err = p.getErrorStream();
            java.lang.Thread thread2 = new java.lang.Thread() {
                public void run() {
                    byte[] buffer = new byte[2048];
                    int c;
                    try {
                        while ((c = err.read(buffer)) > 0)
                            java.lang.System.out.write(buffer, 0, c);
                    } 
                    catch (java.io.IOException e) {
                        throw new java.lang.RuntimeException(e);
                    }
                }
            };
            thread2.start();
            p.waitFor();
            thread1.join();
            thread2.join();
        }
        catch (java.io.IOException e) {
            throw new RuntimeException(e);
        }
        catch (InterruptedException e) {
        }
    }

    private void execStream(panda.core.String path, panda.core.String dir,
            java.lang.Object inHandle, java.lang.Object outHandle, 
            java.lang.String[] args) {
        java.lang.String[] cmd = new java.lang.String[args.length + 1];
        cmd[0] = panda.core.PandaCore.toJavaString(path);
        java.lang.System.arraycopy(args, 0, cmd, 1, args.length);
        try {
            java.lang.Process p = java.lang.Runtime.getRuntime().exec(cmd, null,
                    new java.io.File(PandaCore.toJavaString(dir)));
            if (inHandle != null) {
                java.io.InputStream inStream = (java.io.InputStream) inHandle;
                byte[] buffer = new byte[2048];
                int c;
                try {
                    while ((c = inStream.read(buffer)) > 0)
                        p.getOutputStream().write(buffer, 0, c);
                } 
                catch (java.io.IOException e) {
                    throw new java.lang.RuntimeException(e);
                }
                inStream.close();
                p.getOutputStream().close();
            }
            final java.io.OutputStream out;
            if (outHandle != null)
                out = (java.io.OutputStream) outHandle;
            else {
                out = new java.io.OutputStream() {
                    @Override
                    public void write(int b) throws java.io.IOException {
                    }
                };
            }
            final java.io.InputStream in = p.getInputStream();
            java.lang.Thread thread1 = new java.lang.Thread() {
                public void run() {
                    byte[] buffer = new byte[2048];
                    int c;
                    try {
                        while ((c = in.read(buffer)) > 0)
                            out.write(buffer, 0, c);
                    } 
                    catch (java.io.IOException e) {
                        throw new java.lang.RuntimeException(e);
                    }
                }
            };
            thread1.start();
            final java.io.InputStream err = p.getErrorStream();
            java.lang.Thread thread2 = new java.lang.Thread() {
                public void run() {
                    byte[] buffer = new byte[2048];
                    int c;
                    try {
                        while ((c = err.read(buffer)) > 0)
                            out.write(buffer, 0, c);
                    } 
                    catch (java.io.IOException e) {
                        throw new java.lang.RuntimeException(e);
                    }
                }
            };
            thread2.start();
            p.waitFor();
            thread1.join();
            thread2.join();
        }
        catch (java.io.IOException e) {
            throw new RuntimeException(e);
        }
        catch (InterruptedException e) {
        }
    }

    @Override
    public void execStream_class_panda$core$String_panda$core$String_panda$core$$NativePointer_panda$core$$NativePointer_panda$collections$ListView$LTpanda$core$String$GT(panda.core.String path, panda.core.String dir,
            java.lang.Object inHandle, java.lang.Object outHandle,
            panda.collections.ListView$.$Lpanda$core$String$R args) {
        java.lang.String[] finalArgs = new java.lang.String[args.length_$Rpanda$core$Int32()];
        for (int i = 0; i < finalArgs.length; i++)
            finalArgs[i] = panda.core.PandaCore.toJavaString(args.$ARR_Int32_$Rpanda$core$String(i));
        execStream(path, dir, inHandle, outHandle, finalArgs);
    }
}
