#include "metalc/charsets/common.h"
#include "metalc/ctype.h"
#include "metalc/errno.h"
#include "metalc/limits.h"
#include "metalc/locale.h"
#include "metalc/metalc.h"
#include "metalc/setjmp.h"
#include "metalc/signal.h"
#include "metalc/stdbool.h"
#include "metalc/stdlib.h"
#include "metalc/string.h"


static unsigned g_rand_seed = 0;
static const char *kIntAlphabet = "0123456789abcdefghijklmnopqrstuvwxyz";

extern MetalCRuntimeInfo *mcinternal_runtime_info;
extern mclib_jmp_buf mcinternal_abort_target;

extern const struct mclib_lconv mcinternal_current_lconv;
extern const struct mcinternal_charset_info *mcinternal_ptr_current_charset;


void abort(void) {
    raise(mclib_SIGABRT);

    /* Theoretically we should never get here; the program should exit once the
     * abort signal has been raised. On the off chance that doesn't happen... */
    exit(-1);
}


void srand(unsigned seed) {
    g_rand_seed = seed;
}


void exit(int code) {
    /* TODO: execute atexit handlers here */
    mcinternal_runtime_info->main_return_value = code;
    longjmp(mcinternal_abort_target, INT_MIN);
}


#if 0
double atof(const char *str) {
    double result = 0.0;
    double sign = 1;

    /* Skip leading whitespace */
    while (*str != '\0' && isspace(*str))
        ++str;

    /* If we hit the end of the string, bail. */
    if (*str == '\0') {
        mclib_errno = mclib_EINVAL;
        return 0.0;
    }

    /* Set the sign of the return value and skip over the - or + if present. */
    switch (*str) {
        case '+':
            sign = 1;
            ++str;
            break;
        case '-':
            sign = -1;
            ++str;
            break;
        default:
            /* Not a + or -, no need to do anything. */
            break;
    }

    /* Once we're here there should be a digit. If not */

    return sign * result;
}
#endif


int abs(int x) {
    if (x >= 0)
        return x;
    return -x;
}


long labs(long x) {
    if (x >= 0)
        return x;
    return -x;
}


char *itoa(int value, char *str, int base) {
    return ltoa((long)value, str, base);
}


char *utoa(unsigned value, char *str, int base) {
    return ultoa((unsigned long)value, str, base);
}


char *ltoa(long value, char *str, int base) {
    if ((base < 2) || (base > 36)) {
        mclib_errno = mclib_EINVAL;
        return NULL;
    }

    if ((base == 10) && (value < 0))
        *str++ = '-';

    /* Values are always treated as unsigned if the base is not 10. We also just
     * wrote the sign for `value` (if applicable) so we don't care that it's
     * negative anymore. */
    return ultoa((unsigned long)labs(value), str, base);
}


char *ultoa(unsigned long value, char *str, int base) {
    int i;
    char temp_c;
    char *write_pointer = str;

    if ((base < 2) || (base > 36)) {
        mclib_errno = mclib_EINVAL;
        return NULL;
    }

    do {
        *write_pointer++ = kIntAlphabet[value % base];
        value /= base;
    } while (value != 0);

    *write_pointer = '\0';

    /* When we get here the string is backwards, and write_pointer points past
     * the end of it. Decrement the write pointer so it points to the last
     * character in the string, and swap characters until we meet in the middle.
     */
    --write_pointer;
    for (i = 0; &str[i] != write_pointer; ++i, --write_pointer) {
        temp_c = str[i];
        str[i] = *write_pointer;
        *write_pointer = temp_c;
    }

    return str;
}


unsigned long strtoul(const char *str, const char **endptr, int base) {
    unsigned long value, current_digit;
    char next_char;
    int n_digits_processed;
    char *p_digit;

    /* Skip leading whitespace */
    while (isspace(*str))
        ++str;

    /* We allow a leading '+' (like strtol) but not a leading '-'. */
    if (*str == '+')
        ++str;

    if (base == 0) {
        /* Caller wants us to determine the radix on our own. If this starts with
         * a '0' then it's either a radix or the entire value is 0. */
        if (*str == '0') {
            /* Starts with a 0; if it's followed by x then it's hexadecimal, if
             * followed by a digit then it's octal. */
            next_char = str[1];

            if ((next_char == 'x') || (next_char == 'X'))
                base = 16;
            else if (isdigit(next_char))
                base = 8;
            else {
                /* String is '0' followed by a non-digit character. This must be
                 * just "0". */
                if (endptr)
                    *endptr = str + 1;
                return 0;
            }
        }
        else
            /* String doesn't have an explicit radix, so assume it's base 10. */
            base = 10;
    }
    else if ((base < 2) || (base > 36)) {
        /* If a radix is passed in, it must be between 2 and 36, inclusive. */
        mclib_errno = mclib_EINVAL;
        if (endptr)
            *endptr = str;
        return 0;
    }

    value = 0;
    for (n_digits_processed = 0; *str != '\0'; ++n_digits_processed, ++str) {
        p_digit = strchr(kIntAlphabet, tolower(*str));
        if (p_digit == NULL)
            break;

        current_digit = (unsigned long)((intptr_t)p_digit - (intptr_t)kIntAlphabet);
        if (current_digit >= (unsigned long)base)
            /* This is a valid digit in one of the bases we support, but not in
             * the one we're operating in. Treat it as the end of the number. */
            break;

        value += current_digit;
        value *= base;
    }

    if (n_digits_processed == 0) {
        /* If we haven't processed any digits then this isn't a valid string.
         * Indicate this in @ref errno and return 0. */
        mclib_errno = mclib_EINVAL;
        value = 0;
    }
    else
        mclib_errno = 0;

    if (endptr)
        *endptr = str;
    return value;
}


long strtol(const char *str, const char **endptr, int base) {
    unsigned long magnitude;
    long sign;

    while (isspace(*str))
        ++str;

    if (*str == '+') {
        sign = 1;
        ++str;
    }
    else if (*str == '-') {
        sign = -1;
        ++str;
    }
    else
        sign = 1;

    magnitude = strtoul(str, endptr, base);
    if (mclib_errno != 0)
        return 0;
    if (magnitude > LONG_MAX) {
        mclib_errno = mclib_EOVERFLOW;
        return 0;
    }

    return sign * (long)magnitude;
}


mclib_div_t div(int numer, int denom) {
    mclib_div_t result;

    result.quot = numer / denom;
    result.rem = numer % denom;
    return result;
}


mclib_ldiv_t ldiv(long numer, long denom) {
    mclib_ldiv_t result;

    result.quot = numer / denom;
    result.rem = numer % denom;
    return result;
}


int mblen(const char *str, size_t n) {
    return mcinternal_ptr_current_charset->f_mblen(str, n);
}


int wctomb(char *str, mclib_wchar_t wchar) {
    return mcinternal_ptr_current_charset->f_wctomb(str, wchar);
}


int mbtowc(mclib_wchar_t *pwc, const char *str, size_t n) {
    return mcinternal_ptr_current_charset->f_mbtowc(pwc, str, n);
}


size_t mbstowcs(mclib_wchar_t *pwcs, const char *str, size_t n) {
    size_t out_position;
    ptrdiff_t current_char_len;

    for (out_position = 0; out_position < n; ++out_position) {
        current_char_len = mbtowc(pwcs + out_position, str, current_char_len);

        if (current_char_len < 0) {
            mclib_errno = mclib_EILSEQ;
            return out_position;
        }
        else if (current_char_len == 0)
            return out_position;

        str += current_char_len;
    }

    /* If we get out here then we wrote the maximum number of allowed wide characters
     * before hitting the end of the input string. */
    return out_position;
}


size_t wcstombs(char *str, const mclib_wchar_t *pwcs, size_t n) {
    size_t out_position;
    char buffer[4];
    int wchar_length;

    out_position = 0;
    while (out_position < n) {
        if (*pwcs == 0) {
            *str = '\0';
            return out_position;
        }

        wchar_length = wctomb(buffer, *pwcs);
        if (wchar_length < 0) {
            mclib_errno = mclib_EILSEQ;
            return (size_t)-1;
        }

        if ((out_position + (size_t)wchar_length) > n) {
            /* Not enough space left to write this last character. */
            return out_position;
        }

        memcpy(str, buffer, wchar_length);
        out_position += (size_t)wchar_length;
        ++pwcs;
    }

    /* If we get out here then we wrote exactly the maximum number of bytes allowed
     * before hitting the end of the wchar string. */
    return out_position;
}


void *bsearch(
    const void *key, const void *base, size_t nitems, size_t size,
    int (*cmp)(const void *, const void *)
) {
    const void *partition;
    size_t partition_index;
    int compare_result;

    if (nitems == 0)
        return NULL;
    if (nitems == 1) {
        if (cmp(key, base) == 0)
            return (void *)base;
        return NULL;
    }

    partition_index = nitems / 2;
    partition = (const void *)((const char *)base + (size * partition_index));

    compare_result = cmp(key, partition);
    if (compare_result == 0)
        return (void *)partition;
    if (compare_result > 0)
        /* Item we're looking for is larger than the partition. Readjust the base
         * of our search to be one element past the partition. */
        base = (const void *)((const char *)partition + size);

    return bsearch(key, base, nitems - partition_index, size, cmp);
}

#if METALC_HAVE_LONG_LONG
    mclib_lldiv_t lldiv(long long numer, long long denom) {
        mclib_lldiv_t result;

        result.quot = numer / denom;
        result.rem = numer % denom;
        return result;
    }


    long long llabs(long long x) {
        if (x >= 0)
            return x;
        return -x;
    }


    char *lltoa(long long value, char *str, int base) {
        if ((base < 2) || (base > 36)) {
            mclib_errno = mclib_EINVAL;
            return NULL;
        }

        if ((base == 10) && (value < 0))
            *str++ = '-';

        /* Values are always treated as unsigned if the base is not 10. We also just
         * wrote the sign for `value` (if applicable) so we don't care that it's
         * negative anymore. */
        return ulltoa((unsigned long)labs(value), str, base);
    }


    char *ulltoa(unsigned long long value, char *str, int base) {
        int i;
        char temp_c;
        char *write_pointer = str;

        if ((base < 2) || (base > 36)) {
            mclib_errno = mclib_EINVAL;
            return NULL;
        }

        do {
            *write_pointer++ = kIntAlphabet[value % base];
            value /= base;
        } while (value != 0);

        *write_pointer = '\0';

        /* When we get here the string is backwards, and write_pointer points past
         * the end of it. Decrement the write pointer so it points to the last
         * character in the string, and swap characters until we meet in the middle.
         */
        --write_pointer;
        for (i = 0; &str[i] != write_pointer; ++i, --write_pointer) {
            temp_c = str[i];
            str[i] = *write_pointer;
            *write_pointer = temp_c;
        }

        return str;
    }

    cstdlib_implement(llabs);
    cstdlib_implement(lltoa);
    cstdlib_implement(ulltoa);
    cstdlib_implement(lldiv);
#endif


cstdlib_implement(abort);
cstdlib_implement(abs);
cstdlib_implement(bsearch);
cstdlib_implement(div);
cstdlib_implement(exit);
cstdlib_implement(itoa);
cstdlib_implement(labs);
cstdlib_implement(ldiv);
cstdlib_implement(ltoa);
cstdlib_implement(mblen);
cstdlib_implement(mbstowcs);
cstdlib_implement(mbtowc);
cstdlib_implement(srand);
cstdlib_implement(ultoa);
cstdlib_implement(utoa);
cstdlib_implement(wcstombs);
cstdlib_implement(wctomb);
