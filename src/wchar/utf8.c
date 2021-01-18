#include <metalc/errno.h>
#include <metalc/metalc.h>
#include <metalc/string.h>
#include <metalc/wchar.h>


METALC_INTERNAL int __mcint_utf8_mblen(const char *str, size_t n) {
    unsigned uchr;

    /* A NULL pointer means the caller is asking if the character set is state-dependent.
     * It isn't, so we return 0. */
    if (str == NULL)
        return 0;

    if (n == 0) {
        errno = EINVAL;
        return -1;
    }

    uchr = (unsigned)str[0];

    if (uchr == 0)
        return 0;
    if (uchr <= 127)
        return 1;
    if ((uchr & 0xe0) == 0xc0)
        return 2;
    if ((uchr & 0xf0) == 0xe0)
        return 3;
    if ((uchr & 0xf8) == 0xf0)
        return 4;

    errno = EILSEQ;
    return -1;
}


METALC_INTERNAL int __mcint_utf8_mbtowc(wchar_t *pwc, const char *str, size_t n) {
    wchar_t result;
    int current_char_len;

    /* Caller is asking if this encoding is state-dependent (it isn't). */
    if (str == NULL)
        return 0;

    current_char_len = __mcint_utf8_mblen(str, 1);

    /* We need to examine at least current_char_len bytes to correctly interpret
     * the wide character. If we can't, then consider it an illegal byte sequence
     * and complain. */
    if (n < (size_t)current_char_len) {
        errno = EILSEQ;
        return -1;
    }

    switch (current_char_len) {
        case 0:
            result = 0;
            break;
        case 1:
            result = (unsigned)str[0] & 0x7f;
            break;
        case 2:
            result = (((unsigned)str[0] & 0x1f) << 8) | ((unsigned)str[1] & 0x3f);
            break;
        case 3:
            result = (((unsigned)str[0] & 0x0f) << 14)  \
                   | (((unsigned)str[1] & 0x3f) << 6)   \
                   | ((unsigned)str[2] & 0x3f);
            break;
        case 4:
            result = (((unsigned)str[0] & 0x07) << 18)  \
                   | (((unsigned)str[1] & 0x3f) << 12)  \
                   | (((unsigned)str[2] & 0x3f) << 6)   \
                   | ((unsigned)str[3] & 0x3f);
            break;
        default:
            errno = EILSEQ;
            return -1;
    }

    if (pwc)
        *pwc = result;
    return current_char_len;
}


METALC_INTERNAL int __mcint_utf8_wctomb(char *str, wchar_t wchar) {
    /* Caller is asking if this encoding is state-dependent. It isn't. */
    if (str == NULL)
        return 0;

    if (wchar < 0x80) {
        *str = (char)wchar;
        return 1;
    }
    else if (wchar < 0x800) {
        str[0] = 0xc0 | ((wchar >> 6) & 0x1f);
        str[1] = 0x80 | (wchar & 0x3f);
        return 2;
    }
    else if (wchar < 0x10000) {
        str[0] = 0xe0 | ((wchar >> 12) & 0x0f);
        str[1] = 0x80 | ((wchar >> 6) & 0x3f);
        str[2] = 0x80 | (wchar & 0x3f);
        return 3;
    }
    else if (wchar < 0x110000) {
        str[0] = 0xf0 | ((wchar >> 18) & 0x07);
        str[1] = 0x80 | ((wchar >> 12) & 0x3f);
        str[2] = 0x80 | ((wchar >> 6) & 0x3f);
        str[3] = 0x80 | (wchar & 0x3f);
        return 3;
    }
    else {
        errno = EILSEQ;
        return -1;
    }
}
