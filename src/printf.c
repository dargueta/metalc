#include "metalc/errno.h"
#include "metalc/internal/printf.h"
#include "metalc/stddef.h"
#include "metalc/stdlib.h"
#include "metalc/string.h"


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
METALC_API_INTERNAL
int parse_printf_format_flags(const char *format, struct MCFormatSpecifier *info) {
    int i;

    for (i = 0; format[i] != '\0'; ++i) {
        switch (format[i]) {
            case '-':
                info->justify = -1;
                break;
            case '+':
                info->sign_representation = MCFMT_SIGN__FORCE_POSITIVE;
                break;
            case ' ':
                info->sign_representation = MCFMT_SIGN__SPACE_FOR_POSITIVE;
                break;
            case '#':
                info->has_radix_prefix = 1;
                break;
            case '0':
                info->is_zero_padded = 1;
                break;
            default:
                return i;
        }
    }
    return i;
}


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
METALC_API_INTERNAL
int parse_printf_format_width(const char *format, struct MCFormatSpecifier *info) {
    unsigned long width;
    const char *end;

    mclib_errno = 0;
    width = strtoul(format, &end, 10);

    if (mclib_errno != 0)
        return -1;

    info->minimum_field_width = (unsigned)width;
    return (int)(end - format);
}


/**
 * Examine a format string and determine the floating-point precision.
 *
 * This must be called immediately after @ref parse_printf_format_width. It
 * expects `.` to be the first character. If not, it assumes there's no precision
 * specifier and returns immediately.
 */
METALC_API_INTERNAL
int parse_printf_format_precision(const char *format, struct MCFormatSpecifier *info) {
    unsigned long precision;
    const char *end;
    intptr_t n_read;

    /* If there's no leading period then assume there's no defined precision. */
    if (format[0] != '.') {
        info->fraction_zero_padding = 0;
        info->fraction_precision = 0;
        return 1;
    }

    if (format[1] == '0') {
        info->fraction_zero_padding = 1;
        n_read = 2;
    }
    else
        n_read = 1;

    mclib_errno = 0;
    precision = strtoul(format + n_read, &end, 10);

    if (mclib_errno != 0)
        return -1;
    if (precision > INT_MAX) {
        /* If the format string specifies an absurd width that's bigger than an
         * integer can represent, complain. This is most likely an error in the
         * format string. */
        mclib_errno = mclib_EINVAL;
        return -1;
    }

    info->fraction_precision = (int)precision;
    return (int)(end - format);
}


METALC_API_INTERNAL
enum MCArgumentType int_argtype_from_width(enum MCArgumentWidth width_kind) {
    switch (width_kind) {
        case MCAW_BYTE:
            return MC_AT_CHAR;
        case MCAW_SHORT:
            return MC_AT_SHORT;
        case MCAW_DEFAULT:
            return MC_AT_INT;
        case MCAW_LONG:
            return MC_AT_LONG;
        case MCAW_LONGLONG:
            return MC_AT_LONGLONG;
        default:
            mclib_errno = mclib_EINVAL;
            return -1;
    }
}


METALC_API_INTERNAL
enum MCArgumentType float_argtype_from_width(enum MCArgumentWidth width_kind) {
    if (width_kind == MCAW_DEFAULT)
        return MC_AT_DOUBLE;
    if (width_kind == MCAW_LONG_DOUBLE)
        return MC_AT_LONGDOUBLE;

    mclib_errno = mclib_EINVAL;
    return -1;
}


METALC_API_INTERNAL
int parse_printf_format_type(const char *format, struct MCFormatSpecifier *info) {
    enum MCArgumentWidth width;
    int n_read = 0;

    width = MCAW_DEFAULT;
    n_read = 0;

    switch(format[0]) {
        case '\0':
            /* Hit the end of the format string early -- fail. */
            mclib_errno = mclib_EINVAL;
            return -1;
        case 'h':
            /* Check for `hh` */
            if (format[1] == 'h') {
                /* Yep, this is %hh (possibly with some flags). */
                width = MCAW_BYTE;
                n_read = 2;
            }
            else {
                /* Only got %h (possibly with some flags). */
                width = MCAW_SHORT;
                n_read = 1;
            }
            break;
        case 'j':
            width = MCAW_INTMAX;
            n_read = 1;
            break;
        case 'l':
            /* Check for `ll` *if* we have long long support */
            #if METALC_COMPILE_OPTION_ENABLE_LONGLONG
                if(format[1] == 'l') {
                    width = MCAW_LONGLONG;
                    n_read = 2;
                }
                else {
                    width = MCAW_LONG;
                    n_read = 1;
                }
            #else
                width = MCAW_LONG;
                n_read = 1;
            #endif
            break;
        case 'L':
            width = MCAW_LONG_DOUBLE;
            n_read = 1;
            break;
        case 't':
            width = MCAW_PTRDIFF;
            n_read = 1;
            break;
        case 'z':
            width = MCAW_SIZE_T;
            n_read = 1;
            break;
        default:
            width = MCAW_DEFAULT;
            n_read = 0;
            break;
    }

    info->argument_width = width;

    switch(format[n_read]) {
        case 'c':
            info->argument_type = MC_AT_CHAR;
            break;
        case 'd':
        case 'i':
            info->is_unsigned = 0;
            info->radix = 10;
            info->argument_type = int_argtype_from_width(width);
            break;
        case 'u':
            info->is_unsigned = 1;
            info->radix = 10;
            info->argument_type = int_argtype_from_width(width);
            break;
        case 'o':
            info->is_unsigned = 1;
            info->radix = 8;
            info->argument_type = int_argtype_from_width(width);
            break;
        case 'x':
        case 'X':
            info->is_unsigned = 1;
            info->radix = 16;
            info->argument_type = int_argtype_from_width(width);
            break;
        case 'a':
        case 'A':
        case 'e':
        case 'E':
        case 'f':
        case 'F':
        case 'g':
        case 'G':
            info->radix = 0;
            info->argument_type = float_argtype_from_width(width);
            break;
        case 'n':
        case 'p':
        case 's':
            mclib_errno = mclib_ENOSYS;
            return -1;
        default:
            mclib_errno = mclib_EINVAL;
            return -1;
    }
    return n_read;
}



METALC_API_INTERNAL
int mcinternal_parse_printf_format_specifier(
    const char *format, struct MCFormatSpecifier *info
) {
    int total_read;
    int current_read;

    total_read = 0;

    current_read = parse_printf_format_flags(format, info);
    if (current_read < 0)
        return -total_read;
    total_read = current_read;

    current_read = parse_printf_format_width(format + total_read, info);
    if (current_read < 0)
        return -total_read;
    total_read += current_read;

    current_read = parse_printf_format_precision(format + total_read, info);
    if (current_read < 0)
        return -total_read;
    total_read += current_read;

    current_read = parse_printf_format_type(format + total_read, info);
    if (current_read < 0)
        return -total_read;
    return total_read + current_read;
}
