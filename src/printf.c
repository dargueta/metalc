#include "metalc/ctype.h"
#include "metalc/errno.h"
#include "metalc/internal/printf.h"
#include "metalc/metalc.h"
#include "metalc/stdlib.h"
#include "metalc/string.h"


/**
 * Examine a format string and read the flags.
 *
 * On success, the function returns the number of characters it read. On failure,
 * the number will be negative and errno will be set. The absolute value of the
 * return value is still the number of characters read.
 */
METALC_INTERNAL_ONLY
int parse_printf_format_flags(const char *format, struct MCFormatSpecifier *info) {
    int i;

    info->sign_representation = MCFMT_SIGN__ONLY_NEGATIVE;
    info->justify = MCFMT_JUSTIFY__UNSPECIFIED;
    info->has_radix_prefix = 0;
    mclib_errno = 0;

    for (i = 0; format[i] != '\0'; ++i) {
        switch (format[i]) {
            case '-':
                info->justify = MCFMT_JUSTIFY__LEFT;
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
 * present) will be a positive integer not starting with `0`.
 *
 * The function returns the number of characters read. If the width isn't present,
 * the return value will be 0 and `info->width` will also be 0.
 */
METALC_INTERNAL_ONLY
int parse_printf_format_width(const char *format, struct MCFormatSpecifier *info) {
    unsigned long width;
    const char *end;

    mclib_errno = 0;
    if (!isdigit(format[0])) {
        info->minimum_field_width = 0;
        return 0;
    }

    width = strtoul(format, &end, 10);
    if (mclib_errno != 0)
        return -1;

    if (width > INT_MAX)
        info->minimum_field_width = INT_MAX;
    else
        info->minimum_field_width = (int)width;
    return (int)(end - format);
}


/**
 * Examine a format string and determine the floating-point precision.
 *
 * This must be called immediately after @ref _read_width. It expects `.` to be
 * the first character. If not, it assumes there is no precision specifier and
 * returns immediately.
 */
METALC_INTERNAL_ONLY
int parse_printf_format_precision(const char *format, struct MCFormatSpecifier *info) {
    unsigned long precision;
    const char *end;
    intptr_t n_read;

    mclib_errno = 0;
    if (format[0] == '\0') {
        info->fraction_zero_padding = 0;
        info->fraction_precision = 0;
        return 0;
    }

    /* If there's no leading period then assume there's no defined precision. */
    if (format[0] != '.') {
        info->fraction_zero_padding = 0;
        info->fraction_precision = 0;
        return 0;
    }

    if (format[1] == '0') {
        info->fraction_zero_padding = 1;
        n_read = 2;
    }
    else {
        info->fraction_zero_padding = 0;
        n_read = 1;
    }

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


METALC_INTERNAL_ONLY
enum MCArgumentType int_argtype_from_width(enum MCArgumentWidth width_kind) {
    mclib_errno = 0;
    switch (width_kind) {
        case MCFMT_ARGW__BYTE:
            return MCFMT_ARGT__BYTE;
        case MCFMT_ARGW__SHORT:
            return MCFMT_ARGT__SHORT;
        case MCFMT_ARGW__DEFAULT:
            return MCFMT_ARGT__INT;
        case MCFMT_ARGW__LONG:
            return MCFMT_ARGT__LONG;
#if METALC_COMPILE_OPTION_ENABLE_LONGLONG
        case MCFMT_ARGW__LONGLONG:
            return MCFMT_ARGT__LONGLONG;
#endif
        default:
            mclib_errno = mclib_EINVAL;
            return MCFMT_ARGT__UNKNOWN;
    }
}


METALC_INTERNAL_ONLY
enum MCArgumentType float_argtype_from_width(enum MCArgumentWidth width_kind) {
    mclib_errno = 0;
    if (width_kind == MCFMT_ARGW__DEFAULT)
        return MCFMT_ARGT__DOUBLE;

#ifdef METALC_COMPILE_OPTION_ENABLE_LONGLONG
    if (width_kind == MCFMT_ARGW__LONG_DOUBLE)
        return MCFMT_ARGT__LONGDOUBLE;
#endif

    mclib_errno = mclib_EINVAL;
    return MCFMT_ARGT__UNKNOWN;
}


METALC_INTERNAL_ONLY
int parse_printf_format_type_width_flag(
    const char *format, struct MCFormatSpecifier *info
) {
    mclib_errno = 0;
    switch(format[0]) {
        case 'h':
            /* Check for `hh` */
            if (format[1] == 'h') {
                /* Yep, this is %hh (possibly with some flags). */
                info->argument_width = MCFMT_ARGW__BYTE;
                return 2;
            }

            /* Only got %h (possibly with some flags). */
            info->argument_width = MCFMT_ARGW__SHORT;
            return 1;
        case 'j':
            info->argument_width = MCFMT_ARGW__INTMAX;
            return 1;
        case 'l':
            /* Check for `ll` *if* we have long long support */
#if METALC_COMPILE_OPTION_ENABLE_LONGLONG
            if(format[1] == 'l') {
                info->argument_width = MCFMT_ARGW__LONGLONG;
                return 2;
            }
            info->argument_width = MCFMT_ARGW__LONG;
            return 1;
#else
            info->argument_width = MCFMT_ARGW__LONG;
            return 1;
#endif
        case 'L':
            info->argument_width = MCFMT_ARGW__LONG_DOUBLE;
            return 1;
        case 't':
            info->argument_width = MCFMT_ARGW__PTRDIFF;
            return 1;
        case 'z':
            info->argument_width = MCFMT_ARGW__SIZE_T;
            return 1;
        case '\0':
            /* Hit the end of the format string early -- fail. */
            mclib_errno = mclib_EINVAL;
            return -1;
        default:
            info->argument_width = MCFMT_ARGW__DEFAULT;
            return 0;
    }
}


METALC_INTERNAL_ONLY
int parse_printf_format_type(const char *format, struct MCFormatSpecifier *info) {
    enum MCArgumentType arg_type;
    int n_read;

    n_read = parse_printf_format_type_width_flag(format, info);
    if (n_read < 0)
        return n_read;

    info->use_uppercase = 0;

    switch(format[n_read]) {
        case 'c':
            info->radix = 0;
            info->is_unsigned = 0;
            arg_type = MCFMT_ARGT__CHAR;
            break;
        case 'd':
        case 'i':
            info->is_unsigned = 0;
            info->radix = 10;
            arg_type = int_argtype_from_width(info->argument_width);
            break;
        case 'u':
            info->is_unsigned = 1;
            info->radix = 10;
            arg_type = int_argtype_from_width(info->argument_width);
            break;
        case 'o':
            info->is_unsigned = 1;
            info->radix = 8;
            arg_type = int_argtype_from_width(info->argument_width);
            break;
        case 'X':
            info->use_uppercase = 1;
            /* fall through */
        case 'x':
            info->is_unsigned = 1;
            info->radix = 16;
            arg_type = int_argtype_from_width(info->argument_width);
            break;
        case 'A':
            info->use_scientific_notation = MCFMT_SCINOT__ALWAYS;
            info->radix = 16;
            info->use_uppercase = 1;
            arg_type = float_argtype_from_width(info->argument_width);
            break;
        case 'E':
            info->use_scientific_notation = MCFMT_SCINOT__ALWAYS;
            info->radix = 10;
            info->use_uppercase = 1;
            arg_type = float_argtype_from_width(info->argument_width);
            break;
        case 'F':
            info->use_scientific_notation = MCFMT_SCINOT__NEVER;
            info->radix = 10;
            info->use_uppercase = 1;
            arg_type = float_argtype_from_width(info->argument_width);
            break;
        case 'G':
            info->use_scientific_notation = MCFMT_SCINOT__IF_NEEDED;
            info->use_uppercase = 1;
            info->radix = 10;
            arg_type = float_argtype_from_width(info->argument_width);
            break;
        case 'a':
            info->use_scientific_notation = MCFMT_SCINOT__ALWAYS;
            info->radix = 16;
            arg_type = float_argtype_from_width(info->argument_width);
            break;
        case 'e':
            info->use_scientific_notation = MCFMT_SCINOT__ALWAYS;
            info->radix = 10;
            arg_type = float_argtype_from_width(info->argument_width);
            break;
        case 'f':
            info->use_scientific_notation = MCFMT_SCINOT__NEVER;
            info->radix = 10;
            arg_type = float_argtype_from_width(info->argument_width);
            break;
        case 'g':
            info->use_scientific_notation = MCFMT_SCINOT__IF_NEEDED;
            info->radix = 10;
            arg_type = float_argtype_from_width(info->argument_width);
            break;
        case 'n':
            info->radix = 0;
            /* fall through */
        case 'p':
        case 's':
            mclib_errno = mclib_ENOSYS;
            return -1;
        default:
            mclib_errno = mclib_EINVAL;
            return -1;
    }

    info->argument_type = arg_type;
    /* The +1 is for skipping over the argument type specifier. */
    return n_read + 1;
}


METALC_INTERNAL_ONLY
int parse_printf_format_specifier(const char *format, struct MCFormatSpecifier *info) {
    int total_read;
    int current_read;

    total_read = 0;

    /* This tells the caller that the results are invalid. */
    memset(info, 0, sizeof(*info));
    info->argument_type = MCFMT_ARGT__UNKNOWN;

    current_read = parse_printf_format_flags(format, info);
    if (mclib_errno != 0)
        return -total_read;
    total_read = current_read;

    current_read = parse_printf_format_width(format + total_read, info);
    if (mclib_errno != 0)
        return -total_read;
    total_read += current_read;

    current_read = parse_printf_format_precision(format + total_read, info);
    if (mclib_errno != 0)
        return -total_read;
    total_read += current_read;

    current_read = parse_printf_format_type(format + total_read, info);
    if (mclib_errno != 0)
        return -total_read;
    return total_read + current_read;
}
