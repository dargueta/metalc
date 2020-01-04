#include <metalc/crtinit.h>
#include <metalc/ctype.h>
#include <metalc/errno.h>
#include <metalc/stdarg.h>
#include <metalc/stdint.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>
#include <metalc/string.h>


struct FILE_ {
    intptr_t descriptor;
};


static struct FILE_ internal_stdin_;
static struct FILE_ internal_stdout_;
static struct FILE_ internal_stderr_;

FILE *stdin = &internal_stdin_;
FILE *stdout = &internal_stdout_;
FILE *stderr = &internal_stderr_;


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
    internal_stdin_.descriptor = __mclib_runtime_info->stdin_handle;
    internal_stdout_.descriptor = __mclib_runtime_info->stdout_handle;
    internal_stderr_.descriptor = __mclib_runtime_info->stderr_handle;
    return 0;
}


METALC_API_INTERNAL int stdio_teardown(void) {
    return 0;
}


static int _determine_format(const char *format, struct MCFormatSpecifier *info) {
    (void)format; (void)info;
    return ENOSYS;
}


static size_t _copy_buffer(const char *temp, char **buffer) {
    size_t buffer_size = strlen(temp);

    if (*buffer) {
        strcpy(*buffer, temp);
        *buffer += buffer_size;
    }
    return buffer_size;
}


int vsprintf(char *buffer, const char *format, va_list arg_list) {
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
                itoa(va_arg(arg_list, int), temp, 10);
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
                        itoa(va_arg(arg_list, int), temp, 10);
                        break;
                    case 'u':
                        utoa(va_arg(arg_list, unsigned), temp, 10);
                        break;
                    case 'x':
                    case 'X':
                        utoa(va_arg(arg_list, unsigned), temp, 16);
                        buffer_size = (int)strlen(temp);
                        if (*format == 'X') {
                            for (i = 0; i < buffer_size; ++i)
                                temp[i] = toupper(temp[i]);
                        }
                        break;
                    case 'e':
                    case 'f':
                    case 'g':
                        errno = ENOSYS;
                        return -n_chars_written;
                    default:
                        errno = EINVAL;
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
                                lltoa(va_arg(arg_list, long long), temp, 10);
                                break;
                            case 'u':
                                ulltoa(
                                    va_arg(arg_list, unsigned long long), temp, 10
                                );
                                break;
                            case 'x':
                            case 'X':
                                ulltoa(
                                    va_arg(arg_list, unsigned long long), temp, 16
                                );
                                buffer_size = (int)strlen(temp);
                                if (*format == 'X') {
                                    for (i = 0; i < buffer_size; ++i)
                                        temp[i] = toupper(temp[i]);
                                }
                                break;
                            default:
                                errno = EINVAL;
                                return -n_chars_written;
                        }
                    }
                    else {
                        /* Format is %l_ not %ll_ */
                        switch (*format) {
                            case 'd':
                            case 'i':
                                ltoa(va_arg(arg_list, long), temp, 10);
                                break;
                            case 'u':
                                ultoa(
                                    va_arg(arg_list, unsigned long), temp, 10
                                );
                                break;
                            case 'x':
                            case 'X':
                            case 'e':
                            case 'f':
                            case 'g':
                                /* TODO */
                                errno = ENOSYS;
                                return -n_chars_written;
                            default:
                                errno = EINVAL;
                                return -n_chars_written;
                        }
                    }
                #else
                    /* No long long support */
                    switch (*format) {
                        case 'd':
                        case 'i':
                            ltoa(va_arg(arg_list, long), temp, 10);
                            break;
                        case 'u':
                            ultoa(va_arg(arg_list, unsigned long), temp, 10);
                            break;
                        case 'x':
                        case 'X':
                            /* TODO */
                            errno = ENOSYS;
                            return -n_chars_written;
                        default:
                            errno = EINVAL;
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
                utoa(va_arg(arg_list, unsigned), temp, 10);
                n_chars_written += _copy_buffer(temp, &buffer);
                break;
            case 'x':
            case 'X':
                utoa(va_arg(arg_list, unsigned), temp, 16);
                buffer_size = (int)strlen(temp);
                if (*format == 'X') {
                    for (i = 0; i < buffer_size; ++i)
                        temp[i] = toupper(temp[i]);
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
                errno = ENOSYS;
                return -n_chars_written;
            default:
                /* Else: This is a complex format specifier. */
                format_error = _determine_format(format, &format_info);
                if (format_error != 0) {
                    errno = EINVAL;
                    return -n_chars_written;
                }
                /* Else: Valid format specifier. */
                break;
        }
    }

    /* TODO (dargueta): Finish */

    return n_chars_written;
}


int sprintf(char *buffer, const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = vsprintf(buffer, format, arg_list);
    va_end(arg_list);
    return result;
}


int vfprintf(FILE *file, const char *format, va_list arg_list) {
    char *buffer;
    int n_chars_written;

    n_chars_written = vsprintf(NULL, format, arg_list);
    if (n_chars_written < 0)
        return n_chars_written;

    buffer = malloc(n_chars_written);
    if (buffer == NULL)
        return -1;

    vsprintf(buffer, format, arg_list);
    fwrite(buffer, n_chars_written - 1, 1, file);
    free(buffer);

    return n_chars_written - 1;
}


int fprintf(FILE *file, const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = vfprintf(file, format, arg_list);
    va_end(arg_list);
    return result;
}


int vprintf(const char *format, va_list arg_list) {
    return vfprintf(stdout, format, arg_list);
}


int printf(const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = vprintf(format, arg_list);
    va_end(arg_list);
    return result;
}
