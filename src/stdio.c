#include "metalc/crtinit.h"
#include "metalc/ctype.h"
#include "metalc/errno.h"
#include "metalc/internal/printf.h"
#include "metalc/internal/string.h"
#include "metalc/limits.h"
#include "metalc/stdarg.h"
#include "metalc/stddef.h"
#include "metalc/stdint.h"
#include "metalc/stdio.h"
#include "metalc/stdlib.h"
#include "metalc/string.h"


extern MetalCRuntimeInfo *mcinternal_runtime_info;
extern int fileio_init(void);
extern int fileio_teardown(void);


METALC_API_INTERNAL int stdio_init(void) {
    return fileio_init();
}


METALC_API_INTERNAL int stdio_teardown(void) {
    return fileio_teardown();
}


static int saturated_cast_to_int(size_t value) {
    if (value > INT_MAX)
        return INT_MAX;
    return (int)value;
}


int mcinternal_evaluate_format_specifier(
    const char **format, va_list arg_list, char **output, int n_chars_written,
    size_t limit
) {
    char temp[256];
    int format_length;
    size_t string_length, remaining_chars;
    struct MCFormatSpecifier info;
    const char *string_pointer;

    if ((limit == 0) || ((size_t)n_chars_written >= (limit - 1)))
        remaining_chars = 0;
    else
        remaining_chars = limit - 1 - (size_t)n_chars_written;

    if (**format == '%') {
        if (output && (remaining_chars > 0)) {
            **output = '%';
            ++*output;
        }
        ++*format;
        return 1;
    }

    format_length = mcinternal_parse_printf_format_specifier(*format, &info);
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
            if (output && (remaining_chars > 0)) {
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
             * FIXME: We need to output the radix first if # is present.
             */
            if (info.is_unsigned)
                /* `x`, `X`, `u`, or `o` */
                itoa(va_arg(arg_list, unsigned), temp, info.radix);
            else
                /* d or i */
                itoa(va_arg(arg_list, int), temp, info.radix);

            string_length = strncpy_and_update_buffer(
                temp, (void **)output, remaining_chars
            );
            return saturated_cast_to_int(string_length);

        case MC_AT_LONG:
            if (info.is_unsigned)
                itoa(va_arg(arg_list, unsigned long), temp, info.radix);
            else
                itoa(va_arg(arg_list, long), temp, info.radix);

            string_length = strcpy_and_update_buffer(temp, (void **)output);
            return saturated_cast_to_int(string_length);

        #if METALC_HAVE_LONG_LONG
            case MC_AT_LONGLONG:
                if (info.is_unsigned)
                    itoa(va_arg(arg_list, unsigned long long), temp, info.radix);
                else
                    itoa(va_arg(arg_list, long long), temp, info.radix);

                string_length = strncpy_and_update_buffer(
                    temp, (void **)output, remaining_chars
                );
                return saturated_cast_to_int(string_length);
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
             * us to return a negative value. The caller will think an error
             * occurred but wouldn't have the right errno value. With a carefully
             * crafted string anything using the return value for pointer indexing
             * could be made to write to an arbitrary location in memory. */
            string_length = strlen(string_pointer);

            if (string_length > (size_t)INT_MAX) {
                mclib_errno = mclib_EOVERFLOW;
                return -1;
            }

            if (!output)
                return saturated_cast_to_int(string_length);

            /* Don't bother with padding crap, just output the string. */
            strncpy(
                *output,
                string_pointer,
                (string_length < remaining_chars) ? string_length : remaining_chars
            );
            return saturated_cast_to_int(string_length);

        case MC_AT_FLOAT:
        case MC_AT_DOUBLE:
        case MC_AT_LONGDOUBLE:
            mclib_errno = mclib_ENOSYS;
            return -1;

        default:
            mclib_errno = mclib_EINVAL;
            return -1;
    }
}


int vsnprintf(char *buffer, size_t size, const char *format, va_list arg_list) {
    int n_chars_written, i;

    n_chars_written = 0;

    while (*format != '\0') {
        if (*format != '%') {
            if (buffer && ((size_t)n_chars_written < size))
                *buffer++ = *format;
            ++n_chars_written;
        }
        else {
            i = mcinternal_evaluate_format_specifier(
                &format, arg_list, &buffer, n_chars_written, size
            );
            if (i < 0)
                return -n_chars_written;
            n_chars_written += i;
        }
    }

    return n_chars_written;
}


int vsprintf(char *buffer, const char *format, va_list arg_list) {
    return vsnprintf(buffer, SIZE_MAX, format, arg_list);
}


int sprintf(char *buffer, const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = vsprintf(buffer, format, arg_list);
    va_end(arg_list);
    return result;
}


int snprintf(char *buffer, size_t n, const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = vsnprintf(buffer, n, format, arg_list);
    va_end(arg_list);
    return result;
}


int vfprintf(mclib_FILE *stream, const char *format, va_list arg_list) {
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


int fprintf(mclib_FILE *stream, const char *format, ...) {
    va_list arg_list;
    int result;

    va_start(arg_list, format);
    result = vfprintf(stream, format, arg_list);
    va_end(arg_list);
    return result;
}


int vprintf(const char *format, va_list arg_list) {
    return vfprintf(mclib_stdout, format, arg_list);
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
