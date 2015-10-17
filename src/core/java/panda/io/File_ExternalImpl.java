package panda.io;

import panda.core.PandaCore;

class File_ExternalImpl implements panda.io.File_External {
    @Override
    public boolean exists_$Rpanda$core$Bit(panda.io.File self) {
        java.io.File f = new java.io.File(PandaCore.toJavaString(self.$path));
        return f.exists();
    }

    @Override
    public boolean isDirectory_$Rpanda$core$Bit(panda.io.File self) {
        java.io.File f = new java.io.File(PandaCore.toJavaString(self.$path));
        return f.isDirectory();
    }

    @Override
    public void createDirectory(panda.io.File self) {
        java.io.File f = new java.io.File(PandaCore.toJavaString(self.$path));
        if (!f.mkdir()) {
            if (!f.exists() || !f.isDirectory())
                throw new RuntimeException("FIXME - couldn't create " + f);
        }
    }

    @Override
    public panda.collections.ListView$.$Lpanda$io$File$R list_$Rpanda$collections$ListView$LTpanda$io$File$GT(panda.io.File self) {
        panda.collections.Array$.$Lpanda$io$File$R result = 
                panda.collections.Array$.$Lpanda$io$File$R.createnew$init();
        java.io.File dir = new java.io.File(PandaCore.toJavaString(self.$path));
        java.io.File[] files = dir.listFiles();
        for (int i = 0; i < files.length; i++) {
            result.add_panda$io$File(panda.io.File.createnew$init_panda$core$String(
                    PandaCore.newString(files[i].getPath())));
        }
        return result;
    }

    @Override
    public void delete(panda.io.File self) {
        java.io.File f = new java.io.File(PandaCore.toJavaString(self.$path));
        f.delete(); // FIXME throw IOException on failure
    }

    @Override
    public panda.core.String absolutePath_$Rpanda$core$String(panda.io.File self) {
        java.lang.String raw = panda.core.PandaCore.toJavaString(self.$path);
        raw = new java.io.File(raw).getAbsolutePath();
        return panda.core.PandaCore.newString(raw);
    }
}
