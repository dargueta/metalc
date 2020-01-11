#include <metalc/crtinit.h>
#include <metalc/ctype.h>
#include <metalc/errno.h>
#include <metalc/stdarg.h>
#include <metalc/stdint.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>
#include <metalc/string.h>

extern MetalCRuntimeInfo *__mclib_runtime_info;
extern int fileio_init(void);


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


struct MCFormatSpecifier {
    int alignment;                  /* -1 for left, 1 for right */
    enum MCArgumentType argument_type;
    int width;
    int radix;
    int is_unsigned;
    int is_zero_padded;
    int has_radix_prefix;
    int has_sign;
    int use_scientific_notation;    /* -1 maybe (%g), 1 force (%e) */
    int padding;
    int fraction_zero_padding;
    int fraction_digits;
};


METALC_API_INTERNAL int stdio_init(void) {
    return fileio_init();
}


METALC_API_INTERNAL int stdio_teardown(void) {
    return 0;
}


static int _determine_format(const char *format, struct MCFormatSpecifier *info) {
    (void)format; (void)info;
    return __mcapi_ENOSYS;
}


static size_t _copy_buffer(const char *temp, char **buffer) {
    size_t buffer_size = strlen(temp);

    if (*buffer) {
        strcpy(*buffer, temp);
        *buffer += buffer_size;
    }
    return buffer_size;
}


int __mcapi_vsprintf(char *buffer, const char *format, va_list arg_list) {
    struct MCFormatSpecifier format_info;
    int format_error, n_chars_written, buffer_size, i;
    char temp[256];

    n_chars_written = 0;

    while (*format != '\0') {
        if (*format != '%') {
            if (buffer)
                *buffer++ = *format;
            ++n_chars_written;
            continue;
        }

        /* Hit a % sign. We now must look at the format specifier in the next
         * character. */
        ++format;
        switch (*format) {
            case '%':
                if (buffer)
                    *buffer++ = '%';
                ++n_chars_written;
                break;
            case 'c':
                /* n.b. `char` is promoted to `int` when passed as an argument */
                temp[0] = (char)va_arg(arg_list, int);
                if (buffer)
                    *buffer++ = temp[0];
                ++n_chars_written;
                break;
            case 'd':
            case 'i':
                __mcapi_itoa(va_arg(arg_list, int), temp, 10);
                n_chars_written += _copy_buffer(temp, &buffer);
                break;
            case 'h':
                /* Half size; this is either a `short int` or a `float`. We don't
                 * support floating-point anything yet. Note that shorts are
                 * promoted to ints when passed in so we use `int` not `short`. */
                ++format;
                switch (*format) {
                    case 'd':
                    case 'i':
                        __mcapi_itoa(va_arg(arg_list, int), temp, 10);
                        break;
                    case 'u':
                        __mcapi_utoa(va_arg(arg_list, unsigned), temp, 10);
                        break;
                    case 'x':
                    case 'X':
                        __mcapi_utoa(va_arg(arg_list, unsigned), temp, 16);
                        buffer_size = (int)strlen(temp);
                        if (*format == 'X') {
                            for (i = 0; i < buffer_size; ++i)
                                temp[i] = __mcapi_toupper(temp[i]);
                        }
                        break;
                    case 'e':
                    case 'f':
                    case 'g':
                        __mcapi_errno = __mcapi_ENOSYS;
                        return -n_chars_written;
                    default:
                        __mcapi_errno = __mcapi_EINVAL;
                        return -n_chars_written;
                }
                n_chars_written += _copy_buffer(temp, &buffer);
                ++format;
                break;
            case 'l':
                #if METALC_HAVE_LONG_LONG
                    /* If we have long long support we need two characters of lookahead
                     * to see if the specifier is %ll_ or just %l_. */
                    ++format;
                    if (*format == 'l') {
                        /* Format is %ll_ */
                        ++format;
                        switch (*format) {
                            case 'd':
                            case 'i':
                                __mcapi_lltoa(va_arg(arg_list, long long), temp, 10);
                                break;
                            case 'u':
                                __mcapi_ulltoa(
                                    va_arg(arg_list, unsigned long long), temp, 10
                                );
                                break;
                            case 'x':
                            case 'X':
                                __mcapi_ulltoa(
                                    va_arg(arg_list, unsigned long long), temp, 16
                                );
                                buffer_size = (int)strlen(temp);
                                if (*format == 'X') {
                                    for (i = 0; i < buffer_size; ++i)
                                        temp[i] = __mcapi_toupper(temp[i]);
                                }
                                break;
                            default:
                                __mcapi_errno = __mcapi_EINVAL;
                                return -n_chars_written;
                        }
                    }
                    else {
                        /* Format is %l_ not %ll_ */
                        switch (*format) {
                            case 'd':
                            case 'i':
                                __mcapi_ltoa(va_arg(arg_list, long), temp, 10);
                                break;
                            case 'u':
                                __mcapi_ultoa(
                                    va_arg(arg_list, unsigned long), temp, 10
                                );
                                break;
                            case 'x':
                            case 'X':
                            case 'e':
                            case 'f':
                            case 'g':
                                /* TODO */
                                __mcapi_errno = __mcapi_ENOSYS;
                                return -n_chars_written;
                            default:
                                __mcapi_errno = __mcapi_EINVAL;
                                return -n_chars_written;
                        }
                    }
                #else
                    /* No long long support */
                    switch (*format) {
                        case 'd':
                        case 'i':
                            __mcapi_ltoa(va_arg(arg_list, long), temp, 10);
                            break;
                        case 'u':
                            __mcapi_ultoa(va_arg(arg_list, unsigned long), temp, 10);
                            break;
                        case 'x':
                        case 'X':
                            /* TODO */
                            __mcapi_errno = __mcapi_ENOSYS;
                            return -n_chars_written;
                        default:
                            __mcapi_errno = __mcapi_EINVAL;
                            return -n_chars_written;
                    }
                #endif

                n_chars_written += _copy_buffer(temp, &buffer);
                ++format;
                break;
            case 'n':
                *va_arg(arg_list, int *) = n_chars_written;
                break;
            case 'u':
                __mcapi_utoa(va_arg(arg_list, unsigned), temp, 10);
                n_chars_written += _copy_buffer(temp, &buffer);
                break;
            case 'x':
            case 'X':
                __mcapi_utoa(va_arg(arg_list, unsigned), temp, 16);
                buffer_size = (int)strlen(temp);
                if (*format == 'X') {
                    for (i = 0; i < buffer_size; ++i)
                        temp[i] = __mcapi_toupper(temp[i]);
                }
                if (buffer) {
                    strcpy(temp, buffer);
                    buffer += buffer_size;
                }
                n_chars_written += buffer_size;
                break;
            case 'e':
            case 'f':
            case 'g':
                __mcapi_errno = __mcapi_ENOSYS;
                return -n_chars_written;
            default:
                /* Else: This is a complex format specifier. */
                format_error = _determine_format(format, &format_info);
                if (format_error != 0) {
                    __mcapi_errno = __mcapi_EINVAL;
                    return -n_chars_written;
                }
                /* Else: Valid format specifier. */
                break;
        }
    }

    /* TODO (dargueta): Finish */

    return n_chars_written;
}


__attribute__((nonnull))
int __mcapi_sprintf(char *buffer, const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = __mcapi_vsprintf(buffer, format, arg_list);
    va_end(arg_list);
    return result;
}


__attribute__((nonnull))
int __mcapi_vfprintf(__mcapi_FILE *stream, const char *format, va_list arg_list) {
    char *buffer;
    int n_chars_written;

    n_chars_written = __mcapi_vsprintf(NULL, format, arg_list);
    if (n_chars_written < 0)
        return n_chars_written;

    buffer = __mcapi_malloc(n_chars_written);
    if (buffer == NULL)
        return -1;

    __mcapi_vsprintf(buffer, format, arg_list);
    __mcapi_fwrite(buffer, n_chars_written - 1, 1, stream);
    __mcapi_free(buffer);
    return n_chars_written - 1;
}


__attribute__((nonnull))
int __mcapi_fprintf(__mcapi_FILE *stream, const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = __mcapi_vfprintf(stream, format, arg_list);
    va_end(arg_list);
    return result;
}


__attribute__((nonnull))
int __mcapi_vprintf(const char *format, va_list arg_list) {
    return __mcapi_vfprintf(__mcapi_stdout, format, arg_list);
}


__attribute__((nonnull))
int __mcapi_printf(const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = __mcapi_vprintf(format, arg_list);
    va_end(arg_list);
    return result;
}
