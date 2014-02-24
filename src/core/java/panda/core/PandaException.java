package panda.core;

public class PandaException extends java.lang.RuntimeException {
    private Error pandaError;
    
    public PandaException(Error pandaError) {
        super(panda.core.PandaCore.toJavaString(pandaError.$message));
        this.pandaError = pandaError;
    }
    
    public Error getPandaError() {
        return pandaError;
    }

/*    @Override
    public void printStackTrace(java.io.PrintStream out) {
        out.print(panda.core.PandaCore.toJavaString(
                pandaError.$CNVpanda$core$String()));
    }*/
}