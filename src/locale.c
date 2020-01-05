#include <metalc/errno.h>
#include <metalc/limits.h>
#include <metalc/locale.h>
#include <metalc/string.h>


static const struct __mcapi_lconv kDefaultCLocale = {
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


static struct __mcapi_lconv gCurrentCLocale;


struct LocaleEntry {
    const struct __mcapi_lconv * const locale;
    const char * const name;
};


const struct LocaleEntry gSupportedLocales[] = {
    {&kDefaultCLocale, "C"},
    {&kDefaultCLocale, ""},
    {NULL, NULL}
};


static const struct __mcapi_lconv *_find_locale(const char *name) {
    const struct LocaleEntry *ptr = gSupportedLocales;

    while (ptr->name != NULL) {
        if (__mcapi_strcmp(ptr->name, name) == 0)
            return ptr->locale;
    }
    return NULL;
}


int __mcapi_setlocale(int what, const char *name) {
    const struct __mcapi_lconv *defaults = _find_locale(name);
    if (defaults == NULL)
        return __mcapi_EINVAL;

    switch (what) {
        case __mcapi_LC_ALL:
            __mcapi_memcpy(&gCurrentCLocale, defaults, sizeof(struct __mcapi_lconv));
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


struct __mcapi_lconv* __mcapi_localeconv(void) {
    return &gCurrentCLocale;
}
