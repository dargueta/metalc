#include "metalc/charsets/common.h"
#include "metalc/charsets/utf8.h"
#include "metalc/errno.h"
#include "metalc/limits.h"
#include "metalc/locale.h"
#include "metalc/string.h"


static const struct mclib_lconv _default_lconv_info = {
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
    const struct mclib_lconv * const lconv_info;
};


/* TODO (dargueta) Adjust this if the lib is compiled to only support ASCII. */
static struct mcinternal_charset_info _supported_charsets[] = {
    {
        "utf8",
        mcinternal_utf8_mblen,
        mcinternal_utf8_mbtowc,
        mcinternal_utf8_wctomb
    },
    {NULL, NULL, NULL, NULL}
};


const struct LConvEntry _supported_locales[] = {
    {"C", &_default_lconv_info},
    {"", &_default_lconv_info},
    {NULL, NULL}
};


struct mclib_lconv _current_lconv;
const struct mcinternal_charset_info *_ptr_current_charset = &_supported_charsets[0];


static const struct mclib_lconv *_find_lconv(const char *name) {
    const struct LConvEntry *ptr;

    for (ptr = _supported_locales; ptr->name != NULL; ++ptr) {
        if (strcmp(ptr->name, name) == 0)
            return ptr->lconv_info;
    }
    return NULL;
}


static const struct mcinternal_charset_info *_find_charset(const char *name) {
    const struct mcinternal_charset_info *ptr;

    for (ptr = _supported_charsets; ptr->name != NULL; ++ptr) {
        if (strcmp(ptr->name, name) == 0)
            return ptr;
    }
    return NULL;
}


METALC_API_INTERNAL int locale_init(void) {
    const struct mclib_lconv *default_locale = _find_lconv("C");
    memcpy(&_current_lconv, default_locale, sizeof(_current_lconv));
    return 0;
}


METALC_API_INTERNAL int locale_teardown(void) {
    return 0;
}


int setlocale(int what, const char *name) {
    const struct mclib_lconv *locale;
    const struct mcinternal_charset_info *charset;

    switch (what) {
        case mclib_LC_ALL:
            /* Caller wants to change the entire locale. */
            locale = _find_lconv(name);
            if (locale == NULL)
                return mclib_EINVAL;

            memcpy(&_current_lconv, locale, sizeof(_current_lconv));
            return 0;

        case mclib_LC_CTYPE:
            /* Caller wants to change the default character set. */
            charset = _find_charset(name);
            if (charset == NULL)
                return mclib_EINVAL;
            _ptr_current_charset = charset;
            return 0;

        case mclib_LC_COLLATE:
        case mclib_LC_MONETARY:
        case mclib_LC_NUMERIC:
        case mclib_LC_TIME:
            /* Caller wants to change specific portions of the current locale.
             * We don't support this yet. */
            mclib_errno = mclib_ENOSYS;
            return mclib_ENOSYS;

        default:
            mclib_errno = mclib_EINVAL;
            return mclib_EINVAL;
    }
}


struct mclib_lconv *localeconv(void) {
    return &_current_lconv;
}


cstdlib_implement(setlocale);
cstdlib_implement(localeconv);
