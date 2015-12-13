package panda.core;

class CharWrapper_ExternalImpl implements panda.core.CharWrapper_External {
    @Override
    public boolean get_isWhitespace_$Rpanda$core$Bit(char $this) {
        return java.lang.Character.isWhitespace($this);
    }

    @Override
    public boolean get_isLowercase_$Rpanda$core$Bit(char $this) {
        return java.lang.Character.isLowerCase($this);
    }

    @Override
    public boolean get_isUppercase_$Rpanda$core$Bit(char $this) {
        return java.lang.Character.isUpperCase($this);
    }

    @Override
    public boolean get_isTitlecase_$Rpanda$core$Bit(char $this) {
        return java.lang.Character.isTitleCase($this);
    }

    @Override
    public char toUppercase_$Rpanda$core$Char(char $this) {
        return java.lang.Character.toUpperCase($this);
    }

    @Override
    public char toLowercase_$Rpanda$core$Char(char $this) {
        return java.lang.Character.toLowerCase($this);
    }

    @Override
    public char toTitlecase_$Rpanda$core$Char(char $this) {
        return java.lang.Character.toTitleCase($this);
    }
}
