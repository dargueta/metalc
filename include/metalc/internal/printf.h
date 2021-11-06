/**
 * Internal declarations for processing printf format strings.
 *
 * @file printf.h
 */

#ifndef INCLUDE_METALC_INTERNAL_PRINTF_H_
#define INCLUDE_METALC_INTERNAL_PRINTF_H_

#include "../metalc.h"
#include "../stdarg.h"
#include "../stddef.h"


/**
 * The data type of the element in the format string.
 */
enum MCArgumentType {
    MCFMT_ARGT__UNKNOWN = -1,
    MCFMT_ARGT__CHAR,     /**< For `%%c` */
    MCFMT_ARGT__STRING,   /**< For `%%s` */
    MCFMT_ARGT__BYTE,     /**< For `%%hhd`, `%%hhi`, `%%hhu`, `%%hho`, or `%%hhx` */
    MCFMT_ARGT__SHORT,    /**< For `%%hd`, `%%hi`, `%%hu`, `%%ho`, or `%%hx` */
    MCFMT_ARGT__INT,      /**< For `%%d`, `%%i`, `%%u`, or `%%x` */
    MCFMT_ARGT__LONG,     /**< For `%%ld`, `%%li`, `%%lu`, or `%%lx` */
    /** For `%%lld`, `%%lli`, `%%llu`, or `%%llx`. Not supported on all platforms. */
    MCFMT_ARGT__LONGLONG,
    MCFMT_ARGT__FLOAT,    /**< For `%%hf` */
    MCFMT_ARGT__DOUBLE,   /**< For `%%f`, `%%e`, or `%%g` */

    /** For `%%lf`, `%%le`, or `%%lg`. Not supported on all platforms. */
    MCFMT_ARGT__LONGDOUBLE,
    MCFMT_ARGT__POINTER,  /**< `p` */
    MCFMT_ARGT__N_WRITTEN_POINTER,    /**< `%%n` */
};


enum MCArgumentWidth {
    MCFMT_ARGW__DEFAULT,
    MCFMT_ARGW__BYTE,
    MCFMT_ARGW__SHORT,
    MCFMT_ARGW__INT,
    MCFMT_ARGW__LONG,
    MCFMT_ARGW__LONGLONG,
    MCFMT_ARGW__INTPTR,
    MCFMT_ARGW__SIZE_T,
    MCFMT_ARGW__PTRDIFF,
    MCFMT_ARGW__LONG_DOUBLE
};


#define MCFMT_ARGW__INTMAX MCFMT_ARGW__INTPTR


enum MCSignRepr {
    MCFMT_SIGN__ONLY_NEGATIVE,
    MCFMT_SIGN__FORCE_POSITIVE,
    MCFMT_SIGN__SPACE_FOR_POSITIVE
};


enum MCFieldJustify {
    MCFMT_JUSTIFY__UNSPECIFIED,
    MCFMT_JUSTIFY__LEFT,
    MCFMT_JUSTIFY__RIGHT
};

enum MCSciNotation {
    MCFMT_SCINOT__UNSPECIFIED,
    MCFMT_SCINOT__NEVER = MCFMT_SCINOT__UNSPECIFIED,
    MCFMT_SCINOT__IF_NEEDED,
    MCFMT_SCINOT__ALWAYS
};


/**
 * Information about a format specifier in a printf format string.
 */
struct MCFormatSpecifier {
    /** How to align the text in the rendered field. */
    enum MCFieldJustify justify;

    /** How to represent the sign of numeric arguments. */
    enum MCSignRepr sign_representation;

    /** The datatype of the argument. */
    enum MCArgumentType argument_type;

    /** The width modifier for the argument, if any. */
    enum MCArgumentWidth argument_width;

    /** The minimum width of the fully rendered field, or 0 if not defined. */
    int minimum_field_width;

    /** The radix of the representation of a numeric argument, 0 if not applicable. */
    int radix;

    /** Nonzero if the argument is an unsigned integer, 0 otherwise. */
    int is_unsigned;
    int is_zero_padded;

    /** For numeric arguments, nonzero if the output requires a prefix indicating the
     * radix, i.e. "0", "0x", or "0X". */
    int has_radix_prefix;

    /** If/when to use scientific notation when rendering this field. */
    enum MCSciNotation use_scientific_notation;

    /** The number of trailing zeros to append to the end of a floating-point number.*/
    int fraction_zero_padding;

    /** The number of digits in the fraction portion of the */
    int fraction_precision;

    /** Use uppercase letters for numeric arguments using a radix >10. */
    int use_uppercase;
};


/**
 * Examine a format specifier and read the flags, but not the width or type indicators.
 *
 * For example, for a format specifier "%-04d", @a format is expected to point
 * to the '-' and only "-0" will be read. "4d" are the width and type indicators
 * so they're ignored.
 *
 * @a format is expected to point to the first character past a `%` sign.
 *
 * On success, the function returns the number of characters it read. On failure,
 * the number will be negative and errno will be set. The absolute value of the
 * return value is still the number of characters read.
 */
METALC_API_INTERAL_WITH_ATTR(nonnull)
int parse_printf_format_flags(const char *format, struct MCFormatSpecifier *info);


/**
 * Examine a format string and read the field width.
 *
 * This function must be called after all flags are read. Thus, the width (if
 * present) will be a positive integer @e not starting with `0`. For example,
 * for a format string "%-04d", @a format will point to the '4', and only '4'
 * will be read.
 *
 * The function returns the number of characters read. If the width isn't present,
 * the return value will be 0 and `info->width` will also be 0.
 */
METALC_API_INTERAL_WITH_ATTR(nonnull)
int parse_printf_format_width(const char *format, struct MCFormatSpecifier *info);


/**
 * Parse a printf format specifier and extract the information in them.
 *
 * @param format    A pointer to the beginning of the format string specifier,
 *                  immediately after the introducing `%`. This must not be an
 *                  escaped `%`, i.e. the first character of @a format must not
 *                  be `%`.
 *
 * @param info      A pointer to the structure that will be filled with all the
 *                  settings defined by the format specifier.
 *
 * @return  An integer indicating the number of bytes that were consumed when
 *          processing the format specifier. If an error occurred, the return
 *          value will be negative and @ref errno will be set accordingly.
 */
METALC_API_INTERAL_WITH_ATTR(nonnull)
int mcinternal_parse_printf_format_specifier(const char *format, struct MCFormatSpecifier *info);


/**
 * Examine a format string and determine the floating-point precision.
 *
 * This must be called immediately after @ref parse_printf_format_width. It
 * expects `.` to be the first character. If not, it assumes there's no precision
 * specifier and returns immediately.
 */
METALC_API_INTERAL_WITH_ATTR(nonnull)
int parse_printf_format_precision(const char *format, struct MCFormatSpecifier *info);


METALC_API_INTERNAL
enum MCArgumentType int_argtype_from_width(enum MCArgumentWidth width_kind);


METALC_API_INTERNAL
enum MCArgumentType float_argtype_from_width(enum MCArgumentWidth width_kind);


METALC_API_INTERAL_WITH_ATTR(nonnull)
int parse_printf_format_type_width_flag(
    const char *format, struct MCFormatSpecifier *info
);

METALC_API_INTERAL_WITH_ATTR(nonnull)
int parse_printf_format_type(const char *format, struct MCFormatSpecifier *info);


/**
 * Given a format string, write a single value to the buffer.
 *
 * @todo Add support padding integer values with leading 0s.
 * @todo Add support for %%p.
 * @todo Add support for floating-point numbers.
 * @todo Add support for left- and right-justifying values.
 */
METALC_API_INTERNAL
int mcinternal_evaluate_format_specifier(
    const char **format, va_list arg_list, char **output, int n_chars_written,
    size_t limit
);

#endif  /* INCLUDE_METALC_INTERNAL_PRINTF_H_ */
