enum MCArgumentType {
    MC_AT_CHAR,
    MC_AT_STRING,
    MC_AT_SHORT,
    MC_AT_INT,
    MC_AT_LONG,
    MC_AT_LONGLONG,
    MC_AT_FLOAT,
    MC_AT_DOUBLE,
    MC_AT_LONGDOUBLE,
    MC_AT_POINTER
};


enum MCSignRepr {
    MCFMT_SIGN__ONLY_NEGATIVE,
    MCFMT_SIGN__FORCE_POSITIVE,
    MCFMT_SIGN__SPACE_FOR_POSITIVE
};


struct MCFormatSpecifier {
    int justify;    /* -1 for left, 1 for right */
    enum MCSignRepr sign_representation;
    enum MCArgumentType argument_type;
    int width;
    int radix;
    int is_unsigned;
    int is_zero_padded;
    int has_radix_prefix;
    int use_scientific_notation;    /* -1 maybe (%g), 1 force (%e) */
    unsigned padding;
    int fraction_zero_padding;
    int fraction_digits;
};

