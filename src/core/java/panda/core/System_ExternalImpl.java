package panda.core;

class System_ExternalImpl implements panda.core.System_External {
    @Override
    public panda.core.OperatingSystemInfo operatingSystem() {
        java.lang.String os = java.lang.System.getProperty("os.name");
        panda.core.OperatingSystemType type;
        if (os.startsWith("Mac OS"))
            type = panda.core.OperatingSystemType.$MACOSX;
        else
            type = panda.core.OperatingSystemType.$LINUX;
        return panda.core.OperatingSystemInfo.createnew$constructor(type);
    }

    @Override
    public void exit(int exitCode) {
        java.lang.System.exit(exitCode);
    }

    public void exec(panda.io.File command, panda.io.File dir, 
                panda.collections.PrimitiveArray$LTpanda$core$String$GT args) {
        java.lang.String[] cmd = new java.lang.String[args.$$length + 1];
        cmd[0] = panda.core.PandaCore.toJavaString(command.$path);
        for (int i = 0; i < args.$$length; i++) {
            cmd[i + 1] = panda.core.PandaCore.toJavaString(args.contents[i]);
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

    public void exec(panda.io.File command, panda.io.File dir, 
                panda.collections.ImmutablePrimitiveArray$LTpanda$core$String$GT args) {
        java.lang.String[] cmd = new java.lang.String[args.$$length + 1];
        cmd[0] = panda.core.PandaCore.toJavaString(command.$path);
        for (int i = 0; i < args.$$length; i++) {
            cmd[i + 1] = panda.core.PandaCore.toJavaString(args.contents[i]);
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

    public void execStream(panda.core.String path, panda.core.String dir,
                java.lang.Object inHandle, java.lang.Object outHandle, 
                panda.collections.PrimitiveArray$LTpanda$core$String$GT args) {
        throw new UnsupportedOperationException();
    }

    public void execStream(panda.core.String path, panda.core.String dir,
                java.lang.Object inHandle, java.lang.Object outHandle, 
                panda.collections.ImmutablePrimitiveArray$LTpanda$core$String$GT args) {
        throw new UnsupportedOperationException();
    }}
