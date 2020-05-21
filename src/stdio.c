#include <mcinternal/printf.h>
#include <mcinternal/string.h>
#include <metalc/crtinit.h>
#include <metalc/ctype.h>
#include <metalc/errno.h>
#include <metalc/stdarg.h>
#include <metalc/stdint.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>
#include <metalc/string.h>


extern MetalCRuntimeInfo *__mcint_runtime_info;
extern int fileio_init(void);
extern int fileio_teardown(void);


METALC_API_INTERNAL int stdio_init(void) {
    return fileio_init();
}


METALC_API_INTERNAL int stdio_teardown(void) {
    return fileio_teardown();
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
                n_chars_written += strcpy_and_update_buffer(temp, (void **)&buffer);
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
                        __mcapi_errno = __mcapi_ENOSYS;
                        return -n_chars_written;
                    default:
                        __mcapi_errno = __mcapi_EINVAL;
                        return -n_chars_written;
                }
                n_chars_written += strcpy_and_update_buffer(temp, (void **)&buffer);
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
                                __mcapi_errno = __mcapi_EINVAL;
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
                            ltoa(va_arg(arg_list, long), temp, 10);
                            break;
                        case 'u':
                            ultoa(va_arg(arg_list, unsigned long), temp, 10);
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

                n_chars_written += strcpy_and_update_buffer(temp, (void **)&buffer);
                ++format;
                break;
            case 'n':
                *va_arg(arg_list, int *) = n_chars_written;
                break;
            case 'u':
                utoa(va_arg(arg_list, unsigned), temp, 10);
                n_chars_written += strcpy_and_update_buffer(temp, (void **)&buffer);
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


int sprintf(char *buffer, const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = vsprintf(buffer, format, arg_list);
    va_end(arg_list);
    return result;
}


int vfprintf(__mcapi_FILE *stream, const char *format, va_list arg_list) {
    char *buffer;
    int n_chars_written;

    n_chars_written = vsprintf(NULL, format, arg_list);
    if (n_chars_written < 0)
        return n_chars_written;

    buffer = malloc(n_chars_written);
    if (buffer == NULL)
        return -1;

    vsprintf(buffer, format, arg_list);
    fwrite(buffer, n_chars_written - 1, 1, stream);
    free(buffer);
    return n_chars_written - 1;
}


int fprintf(__mcapi_FILE *stream, const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = vfprintf(stream, format, arg_list);
    va_end(arg_list);
    return result;
}


int vprintf(const char *format, va_list arg_list) {
    return vfprintf(__mcapi_stdout, format, arg_list);
}


int printf(const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = vprintf(format, arg_list);
    va_end(arg_list);
    return result;
}


cstdlib_implement(vsprintf);
cstdlib_implement(sprintf);
cstdlib_implement(vprintf);
cstdlib_implement(printf);
cstdlib_implement(vfprintf);
cstdlib_implement(fprintf);
