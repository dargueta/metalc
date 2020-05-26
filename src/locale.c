#include "metalc/charsets/common.h"
#include "metalc/charsets/utf8.h"
#include "metalc/errno.h"
#include "metalc/limits.h"
#include "metalc/locale.h"
#include "metalc/string.h"


static const struct __mcapi_lconv _default_lconv_info = {
    ".",        /* decimal_point */
    "",         /* thousands_sep */
    "",         /* grouping */
    "",         /* int_curr_symbol */
    "",         /* currency_symbol */
    "",         /* mon_decimal_point */
    "",         /* mon_thousands_sep */
    "",         /* mon_grouping */
    "",         /* positive_sign */
    "",         /* negative_sign */
    CHAR_MAX,   /* frac_digits */
    CHAR_MAX,   /* p_cs_precedes */
    CHAR_MAX,   /* n_cs_precedes */
    CHAR_MAX,   /* p_sep_by_space */
    CHAR_MAX,   /* n_sep_by_space */
    CHAR_MAX,   /* p_sign_posn */
    CHAR_MAX,   /* n_sign_posn */
    CHAR_MAX,   /* int_frac_digits */
    CHAR_MAX,   /* int_p_cs_precedes */
    CHAR_MAX,   /* int_n_cs_precedes */
    CHAR_MAX,   /* int_p_sep_by_space */
    CHAR_MAX,   /* int_n_sep_by_space */
    CHAR_MAX,   /* int_p_sign_posn */
    CHAR_MAX    /* int_n_sign_posn */
};


struct LConvEntry {
    const char * const name;
    const struct __mcapi_lconv * const lconv_info;
};


static struct __mcint_charset_info _supported_charsets[] = {
    {
        "utf8",
        __mcint_utf8_mblen,
        __mcint_utf8_mbtowc,
        __mcint_utf8_wctomb
    },
    {NULL, NULL, NULL, NULL}
};


const struct LConvEntry _supported_locales[] = {
    {"C", &_default_lconv_info},
    {"", &_default_lconv_info},
    {NULL, NULL}
};


const struct __mcapi_lconv *_current_lconv = _supported_locales[0].lconv_info;
const struct __mcint_charset_info *_current_charset = &_supported_charsets[0];


static const struct __mcapi_lconv *_find_lconv(const char *name) {
    const struct LConvEntry *ptr;

    for (ptr = _supported_locales; ptr->name != NULL; ++ptr) {
        if (strcmp(ptr->name, name) == 0)
            return ptr->lconv_info;
    }
    return NULL;
}


static const struct __mcint_charset_info *_find_charset(const char *name) {
    const struct __mcint_charset_info *ptr;

    for (ptr = _supported_charsets; ptr->name != NULL; ++ptr) {
        if (strcmp(ptr->name, name) == 0)
            return ptr;
    }
    return NULL;
}


int setlocale(int what, const char *name) {
    const struct __mcapi_lconv *locale;
    const struct __mcint_charset_info *charset;

    switch (what) {
        case __mcapi_LC_ALL:
            locale = _find_lconv(name);
            if (locale == NULL)
                return __mcapi_EINVAL;
            _current_lconv = locale;
            return 0;
        case __mcapi_LC_CTYPE:
            charset = _find_charset(name);
            if (charset == NULL)
                return __mcapi_EINVAL;
            _current_charset = charset;
            return 0;
        case __mcapi_LC_COLLATE:
        case __mcapi_LC_MONETARY:
        case __mcapi_LC_NUMERIC:
        case __mcapi_LC_TIME:
            __mcapi_errno = __mcapi_ENOSYS;
            return __mcapi_ENOSYS;
        default:
            __mcapi_errno = __mcapi_EINVAL;
            return __mcapi_EINVAL;
    }
}


struct __mcapi_lconv *localeconv(void) {
    /* Deliberately discard the const pointer because that's how the C standard
     * library defines the function. */
    return (struct __mcapi_lconv *)_current_lconv;
}


cstdlib_implement(setlocale);
cstdlib_implement(localeconv);
