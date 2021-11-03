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
    MC_AT_UNKNOWN,
    MC_AT_CHAR,     /**< For `%%c` */
    MC_AT_STRING,   /**< For `%%s` */
    MC_AT_BYTE,     /**< For `%%hhd`, `%%hhi`, `%%hhu`, `%%hho`, or `%%hhx` */
    MC_AT_SHORT,    /**< For `%%hd`, `%%hi`, `%%hu`, `%%ho`, or `%%hx` */
    MC_AT_INT,      /**< For `%%d`, `%%i`, `%%u`, or `%%x` */
    MC_AT_LONG,     /**< For `%%ld`, `%%li`, `%%lu`, or `%%lx` */
    /** For `%%lld`, `%%lli`, `%%llu`, or `%%llx`. Not supported on all platforms. */
    MC_AT_LONGLONG,
    MC_AT_FLOAT,    /**< For `%%hf` */
    MC_AT_DOUBLE,   /**< For `%%f`, `%%e`, or `%%g` */

    /** For `%%lf`, `%%le`, or `%%lg`. Not supported on all platforms. */
    MC_AT_LONGDOUBLE,
    MC_AT_POINTER,  /**< `p` */
    MC_AT_N_WRITTEN_POINTER,    /**< `%%n` */
};


enum MCArgumentWidth {
    MCAW_DEFAULT,
    MCAW_BYTE,
    MCAW_SHORT,
    MCAW_INT,
    MCAW_LONG,
    MCAW_LONGLONG,
    MCAW_INTPTR,
    MCAW_SIZE_T,
    MCAW_PTRDIFF,
    MCAW_LONG_DOUBLE
};


#define MCAW_INTMAX MCAW_INTPTR


enum MCSignRepr {
    MCFMT_SIGN__ONLY_NEGATIVE,
    MCFMT_SIGN__FORCE_POSITIVE,
    MCFMT_SIGN__SPACE_FOR_POSITIVE
};


/**
 * Information about a format specifier in a printf format string.
 */
struct MCFormatSpecifier {
    /**
     * How to align the field.
     *
     * There are three possible values:
     *
     * * -1: Left-justify the field.
     * * 0: The alignment of the field wasn't defined in the format specifier.
     * * 1: Right-justify the field.
     */
    int justify;
    enum MCSignRepr sign_representation;
    enum MCArgumentType argument_type;
    enum MCArgumentWidth argument_width;
    /** The minimum width of the field, or 0 if not defined. */
    int minimum_field_width;
    int radix;
    int is_unsigned;
    int is_zero_padded;
    int has_radix_prefix;
    int use_scientific_notation;    /**< -1 maybe (%g), 1 force (%e) */
    int padding;
    int fraction_zero_padding;
    int fraction_precision;
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
