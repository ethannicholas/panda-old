package panda.core;

class Int32Wrapper_ExternalImpl implements panda.core.Int32Wrapper_External {
    @Override
    public int get_length_$Rpanda$core$Int32(int self) {
        return 32 - java.lang.Integer.numberOfLeadingZeros(self);
    }
}
