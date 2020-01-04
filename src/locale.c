#include <metalc/errno.h>
#include <metalc/limits.h>
#include <metalc/locale.h>
#include <metalc/string.h>


static const struct lconv kDefaultCLocale = {
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


static struct lconv gCurrentCLocale;


struct LocaleEntry {
    const struct lconv * const locale;
    const char * const name;
};


const struct LocaleEntry gSupportedLocales[] = {
    {&kDefaultCLocale, "C"},
    {&kDefaultCLocale, ""},
    {NULL, NULL}
};


static const struct lconv *_find_locale(const char *name) {
    const struct LocaleEntry *ptr = gSupportedLocales;

    while (ptr->name != NULL) {
        if (strcmp(ptr->name, name) == 0)
            return ptr->locale;
    }
    return NULL;
}


int setlocale(int what, const char *name) {
    const struct lconv *defaults = _find_locale(name);
    if (defaults == NULL)
        return EINVAL;

    switch (what) {
        case LC_ALL:
            memcpy(&gCurrentCLocale, defaults, sizeof(struct lconv));
            return 0;
        case LC_COLLATE:
        case LC_CTYPE:
        case LC_MONETARY:
        case LC_NUMERIC:
        case LC_TIME:
            errno = ENOSYS;
            return ENOSYS;
        default:
            errno = EINVAL;
            return EINVAL;
    }
}


struct lconv* localeconv(void) {
    return &gCurrentCLocale;
}
