#include <metalc/errno.h>
#include <metalc/limits.h>
#include <metalc/locale.h>
#include <metalc/string.h>


static const struct __mcapi_lconv _default_c_locale = {
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


static struct __mcapi_lconv _current_c_locale;


struct LocaleEntry {
    const struct __mcapi_lconv * const locale;
    const char * const name;
};


const struct LocaleEntry _supported_locales[] = {
    {&_default_c_locale, "C"},
    {&_default_c_locale, ""},
    {NULL, NULL}
};


static const struct __mcapi_lconv *_find_locale(const char *name) {
    const struct LocaleEntry *ptr = _supported_locales;

    for (ptr = _supported_locales; ptr->name != NULL; ++ptr) {
        if (strcmp(ptr->name, name) == 0)
            return ptr->locale;
    }
    return NULL;
}


int setlocale(int what, const char *name) {
    const struct __mcapi_lconv *defaults = _find_locale(name);
    if (defaults == NULL)
        return __mcapi_EINVAL;

    switch (what) {
        case __mcapi_LC_ALL:
            memcpy(&_current_c_locale, defaults, sizeof(*defaults));
            return 0;
        case __mcapi_LC_COLLATE:
        case __mcapi_LC_CTYPE:
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


struct __mcapi_lconv* localeconv(void) {
    return &_current_c_locale;
}


cstdlib_implement(setlocale);
cstdlib_implement(localeconv);
