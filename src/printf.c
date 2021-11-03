#include "metalc/ctype.h"
#include "metalc/errno.h"
#include "metalc/internal/printf.h"
#include "metalc/stddef.h"
#include "metalc/stdlib.h"
#include "metalc/string.h"


int parse_printf_format_flags(const char *format, struct MCFormatSpecifier *info) {
    int i;

    mclib_errno = 0;
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
        return 1;
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


enum MCArgumentType int_argtype_from_width(enum MCArgumentWidth width_kind) {
    mclib_errno = 0;
    switch (width_kind) {
        case MCAW_BYTE:
            return MC_AT_BYTE;
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
            return MC_AT_UNKNOWN;
    }
}


enum MCArgumentType float_argtype_from_width(enum MCArgumentWidth width_kind) {
    mclib_errno = 0;
    if (width_kind == MCAW_DEFAULT)
        return MC_AT_DOUBLE;

#ifdef METALC_COMPILE_OPTION_ENABLE_LONGLONG
    if (width_kind == MCAW_LONG_DOUBLE)
        return MC_AT_LONGDOUBLE;
#endif

    mclib_errno = mclib_EINVAL;
    return MC_AT_UNKNOWN;
}


int parse_printf_format_type(const char *format, struct MCFormatSpecifier *info) {
    enum MCArgumentWidth width;
    enum MCArgumentType arg_type;
    int n_read;

    mclib_errno = 0;
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
    info->use_uppercase = 0;

    switch(format[n_read]) {
        case 'c':
            info->radix = 0;
            arg_type = MC_AT_CHAR;
            break;
        case 'd':
        case 'i':
            info->is_unsigned = 0;
            info->radix = 10;
            arg_type = int_argtype_from_width(width);
            break;
        case 'u':
            info->is_unsigned = 1;
            info->radix = 10;
            arg_type = int_argtype_from_width(width);
            break;
        case 'o':
            info->is_unsigned = 1;
            info->radix = 8;
            arg_type = int_argtype_from_width(width);
            break;
        case 'X':
            info->use_uppercase = 1;
            /* fall through */
        case 'x':
            info->is_unsigned = 1;
            info->radix = 16;
            arg_type = int_argtype_from_width(width);
            break;
        case 'A':
            info->radix = 16;
            info->use_uppercase = 1;
            arg_type = float_argtype_from_width(width);
            break;
        case 'E':
        case 'F':
        case 'G':
            info->use_uppercase = 1;
            info->radix = 10;
            arg_type = float_argtype_from_width(width);
            break;
        case 'a':
            info->radix = 16;
            arg_type = float_argtype_from_width(width);
            break;
        case 'e':
        case 'f':
        case 'g':
            info->radix = 10;
            arg_type = float_argtype_from_width(width);
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
    /* The +1 is for the argument type */
    return n_read + 1;
}


int mcinternal_parse_printf_format_specifier(
    const char *format, struct MCFormatSpecifier *info
) {
    int total_read;
    int current_read;

    total_read = 0;

    /* This tells the caller that the results are invalid. */
    memset(info, 0, sizeof(*info));
    info->argument_type = MC_AT_UNKNOWN;

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
