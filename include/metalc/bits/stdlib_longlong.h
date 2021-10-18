/**
 * Definitions for optional functions in stdlib.h if `long long` support is enabled.
 *
 * @file stdlib_longlong.h
 */

#ifndef METALC_BITS_STDLIB_LONGLONG_H_
#define METALC_BITS_STDLIB_LONGLONG_H_

#include "../metalc.h"


typedef struct {
    long long quot, rem;
} mclib_lldiv_t;


long long llabs(long long x);      /* done */
long long atoll(const char *str);
long long strtoll(const char *str, const char **endptr, int base);
unsigned long long strtoull(const char *str, const char **endptr, int base);
mclib_lldiv_t lldiv(long long numer, long long denom);

/* Nonstandard */
char *lltoa(long long value, char *buf, int base);
char *ulltoa(unsigned long long value, char *str, int base);

#ifndef METALC_DISABLE_STDLIB_DEFS
    #define lldiv_t mclib_lldiv_t
#endif

cstdlib_export_with_attr(llabs, const);
cstdlib_export_with_attr(atoll, pure);
cstdlib_export_with_attr(strtoll, pure);
cstdlib_export_with_attr(strtoull, pure);
cstdlib_export_with_attr(lldiv, const);
cstdlib_export(lltoa);
cstdlib_export(ulltoa);

#endif  /* METALC_BITS_STDLIB_LONGLONG_H_ */
