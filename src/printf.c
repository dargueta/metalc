#include <metalc/errno.h>
#include <metalc/bits/printf.h>


/**
 * Examine a format string and read the flags.
 *
 * On success, the function returns the number of characters it read. On failure,
 * the number will be negative and errno will be set. The absolute value of the
 * return value is still the number of characters read.
 */
static int _read_flags(const char *format, struct MCFormatSpecifier *info) {
    int i;

    for (i = 0; format[i] != '\0'; ++i) {
        switch (format[i]) {
            case '-':
                info->justify = -1;
                break;
            case '+':
                info->sign_rep = MCSignRepr::MCFMT_SIGN__FORCE_POSITIVE;
                break;
            case ' ':
                info->sign_rep = MCSignRepr::MCFMT_SIGN__SPACE_FOR_POSITIVE;
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


static int _read_width(const char *format, struct MCFormatSpecifier *info) {

}


static int _read_precision(const char *format, struct MCFormatSpecifier *info) {

}


static int _read_length(const char *format, struct MCFormatSpecifier *info) {

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
