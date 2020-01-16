#include <limits.h>

#include <metalc/ctype.h>
#include <metalc/errno.h>
#include <metalc/metalc.h>
#include <metalc/setjmp.h>
#include <metalc/stdbool.h>
#include <metalc/stdlib.h>
#include <metalc/signal.h>

static unsigned g_rand_seed = 0;
static const char *kIntAlphabet = "0123456789abcdefghijklmnopqrstuvwxyz";

extern MetalCRuntimeInfo *__mclib_runtime_info;
extern __mcapi_jmp_buf __mclib_abort_target;


void abort(void) {
    __mcapi_raise(__mcapi_SIGABRT);

    /* Theoretically we should never get here; the program should exit once the
     * abort signal has been raised. On the off chance that doesn't happen... */
    exit(-1);
}


void srand(unsigned seed) {
    g_rand_seed = seed;
}


void exit(int code) {
    /* TODO: execute atexit handlers here */
    __mclib_runtime_info->main_return_value = code;
    __mcapi_longjmp(__mclib_abort_target, INT_MIN);
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
        __mcapi_errno = __mcapi_EINVAL;
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
        __mcapi_errno = __mcapi_EINVAL;
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
        __mcapi_errno = __mcapi_EINVAL;
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


__mcapi_div_t div(int numer, int denom) {
    __mcapi_div_t result;

    result.quot = numer / denom;
    result.rem = numer % denom;
    return result;
}


__mcapi_ldiv_t ldiv(long numer, long denom) {
    __mcapi_ldiv_t result;

    result.quot = numer / denom;
    result.rem = numer % denom;
    return result;
}


#if METALC_HAVE_LONG_LONG
    __mcapi_lldiv_t lldiv(long long numer, long long denom) {
        __mcapi_lldiv_t result;

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
            __mcapi_errno = __mcapi_EINVAL;
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
            __mcapi_errno = __mcapi_EINVAL;
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
cstdlib_implement(srand);
cstdlib_implement(exit);
cstdlib_implement(abs);
cstdlib_implement(labs);
cstdlib_implement(itoa);
cstdlib_implement(utoa);
cstdlib_implement(ltoa);
cstdlib_implement(ultoa);
cstdlib_implement(div);
cstdlib_implement(ldiv);
