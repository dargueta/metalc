#ifndef INCLUDE_METALC_LOCALE_H_
#define INCLUDE_METALC_LOCALE_H_

#include <metalc/metalc.h>

#define __mcapi_LC_ALL      0
#define __mcapi_LC_COLLATE  1
#define __mcapi_LC_CTYPE    2
#define __mcapi_LC_MONETARY 3
#define __mcapi_LC_NUMERIC  4
#define __mcapi_LC_TIME     5


struct __mcapi_lconv {
    char *decimal_point;
    char *thousands_sep;
    char *grouping;
    char *int_curr_symbol;
    char *currency_symbol;
    char *mon_decimal_point;
    char *mon_thousands_sep;
    char *mon_grouping;
    char *positive_sign;
    char *negative_sign;
    char frac_digits;
    char p_cs_precedes;
    char n_cs_precedes;
    char p_sep_by_space;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
    char int_frac_digits;
    char int_p_cs_precedes;
    char int_n_cs_precedes;
    char int_p_sep_by_space;
    char int_n_sep_by_space;
    char int_p_sign_posn;
    char int_n_sign_posn;
};


METALC_API_EXPORT int __mcapi_setlocale(int what, const char *name);
METALC_API_EXPORT struct __mcapi_lconv* __mcapi_localeconv(void);


#endif  /* INCLUDE_METALC_LOCALE_H_ */
