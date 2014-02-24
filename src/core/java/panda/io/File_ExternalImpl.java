package panda.io;

import panda.core.PandaCore;

class File_ExternalImpl implements panda.io.File_External {
    @Override
    public boolean exists(panda.io.File self) {
        java.io.File f = new java.io.File(PandaCore.toJavaString(self.$path));
        return f.exists();
    }

    @Override
    public boolean isDirectory(panda.io.File self) {
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
    public panda.collections.Array$LTpanda$io$File$GT list(panda.io.File self) {
        panda.collections.Array$LTpanda$io$File$GT result = 
                new panda.collections.Array$LTpanda$io$File$GT();
        java.io.File dir = new java.io.File(PandaCore.toJavaString(self.$path));
        java.io.File[] files = dir.listFiles();
        panda.io.File[] contents = new panda.io.File[files.length];
        for (int i = 0; i < files.length; i++) {
            contents[i] = panda.io.File.createnew$constructor(
                    PandaCore.newString(files[i].getPath()));
        }
        result.$$length = files.length;
        result.contents = contents;
        return result;
    }

    @Override
    public void delete(panda.io.File self) {
        java.io.File f = new java.io.File(PandaCore.toJavaString(self.$path));
        f.delete(); // FIXME throw IOException on failure
    }

    @Override
    public panda.core.String absolutePath(panda.io.File self) {
        java.lang.String raw = panda.core.PandaCore.toJavaString(self.$path);
        raw = new java.io.File(raw).getAbsolutePath();
        return panda.core.PandaCore.newString(raw);
    }
}
