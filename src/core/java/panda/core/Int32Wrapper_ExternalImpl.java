package panda.core;

class Int32Wrapper_ExternalImpl implements panda.core.Int32Wrapper_External {
    @Override
    public byte get_length_$Rpanda$core$UInt8(int self) {
        return (byte) (32 - java.lang.Integer.numberOfLeadingZeros(self));
    }
}
