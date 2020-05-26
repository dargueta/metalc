#include "metalc/crtinit.h"
#include "metalc/ctype.h"
#include "metalc/errno.h"
#include "metalc/internal/printf.h"
#include "metalc/internal/string.h"
#include "metalc/limits.h"
#include "metalc/stdarg.h"
#include "metalc/stdint.h"
#include "metalc/stdio.h"
#include "metalc/stdlib.h"
#include "metalc/string.h"


extern MetalCRuntimeInfo *__mcint_runtime_info;
extern int fileio_init(void);
extern int fileio_teardown(void);


METALC_API_INTERNAL int stdio_init(void) {
    return fileio_init();
}


METALC_API_INTERNAL int stdio_teardown(void) {
    return fileio_teardown();
}


int __mcint_evaluate_format_specifier(
    const char **format, va_list arg_list, char **output, int n_chars_written
) {
    char temp[256];
    int format_length;
    size_t string_length;
    struct MCFormatSpecifier info;
    const char *string_pointer;

    if (**format == '%') {
        if (output) {
            **output = '%';
            ++*output;
        }
        ++*format;
        return 1;
    }

    format_length = __mcint_parse_printf_format_specifier(*format, &info);
    if (format_length < 0)
        return -1;

    *format += (size_t)format_length;

    /* `**format` points to the first character in the format string *after* the
     * introductory '%'. Look at that character and increment `*format` so we
     * don't have to do that later. */
    switch (info.argument_type) {
        case MC_AT_CHAR:
            /* n.b. `char` is promoted to `int` when passed as an argument */
            temp[0] = (char)va_arg(arg_list, int);
            if (output){
                **output = temp[0];
                ++*output;
            }
            return 1;

        case MC_AT_BYTE:
        case MC_AT_SHORT:
        case MC_AT_INT:
            /* This can be d, i, u, x, X, o, and their h or hh variants.
             * We don't care if the argument is a short or byte, since they get
             * promoted to integers when passed as arguments.
             *
             * FIXME: We need to output the radix first.
             */
            if (info.is_unsigned)
                /* `x`, `X`, `u`, or `o` */
                itoa(va_arg(arg_list, unsigned), temp, info.radix);
            else
                /* d or i */
                itoa(va_arg(arg_list, int), temp, info.radix);

            return strcpy_and_update_buffer(temp, (void **)output);

        case MC_AT_LONG:
            if (info.is_unsigned)
                itoa(va_arg(arg_list, unsigned long), temp, info.radix);
            else
                itoa(va_arg(arg_list, long), temp, info.radix);

            return strcpy_and_update_buffer(temp, (void **)output);

        #if METALC_HAVE_LONG_LONG
            case MC_AT_LONGLONG:
                if (info.is_unsigned)
                    itoa(va_arg(arg_list, unsigned long long), temp, info.radix);
                else
                    itoa(va_arg(arg_list, long long), temp, info.radix);

                return strcpy_and_update_buffer(temp, (void **)output);
        #endif

        case MC_AT_N_WRITTEN_POINTER:
            *va_arg(arg_list, int *) = n_chars_written;
            return 0;

        case MC_AT_STRING:
            string_pointer = va_arg(arg_list, char *);

            /* Determine the length of the string we need to copy, and fail if
             * the number of bytes in the string exceeds the maximum value we
             * can return.
             *
             * If the string is too long, it gets copied successfully but the
             * number of bytes written will overflow our counter. This'll cause
             * us to return a negative value. The caller think know an error
             * occurred but wouldn't have the right errno value. With a carefully
             * crafted string anything using the return value for pointer indexing
             * could be made to write to an arbitrary location in memory. */
            string_length = strlen(string_pointer);
            if (string_length > (size_t)INT_MAX) {
                __mcapi_errno = __mcapi_EOVERFLOW;
                return -1;
            }

            if (!output)
                return strlen(string_pointer);

            /* Don't bother with padding crap, just output the string. */
            strncpy(*output, string_pointer, string_length);
            return (int)string_length;

        case MC_AT_FLOAT:
        case MC_AT_DOUBLE:
        case MC_AT_LONGDOUBLE:
            __mcapi_errno = __mcapi_ENOSYS;
            return -1;

        default:
            __mcapi_errno = __mcapi_EINVAL;
            return -1;
    }
}


int vsprintf(char *buffer, const char *format, va_list arg_list) {
    int n_chars_written, i;

    n_chars_written = 0;

    while (*format != '\0') {
        if (*format != '%') {
            if (buffer)
                *buffer++ = *format;
            ++n_chars_written;
        }
        else {
            i = __mcint_evaluate_format_specifier(&format, arg_list, &buffer, n_chars_written);
            if (i < 0)
                return -n_chars_written;
            n_chars_written += i;
        }
    }

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
