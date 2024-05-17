/**
 * Definitions for optional functions in stdlib.h if `long long` support is enabled.
 *
 * @file stdlib_longlong.h
 */

#ifndef METALC_BITS_STDLIB_LONGLONG_H_
#define METALC_BITS_STDLIB_LONGLONG_H_

#include "../metalc.h"

typedef struct
{
    long long quot, rem;
} mclib_lldiv_t;

#define atoll(str) strtoll((str), NULL, 10)

METALC_EXPORT
METALC_ATTR__CONST_FUNC
long long llabs(long long x); /* done */

METALC_EXPORT
METALC_ATTR__REPRODUCIBLE
long long strtoll(const char *str, const char **endptr, int base);

METALC_EXPORT
METALC_ATTR__REPRODUCIBLE
unsigned long long strtoull(const char *str, const char **endptr, int base);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
mclib_lldiv_t lldiv(long long numer, long long denom);

/* Nonstandard */
METALC_EXPORT char *lltoa(long long value, char *buf, int base);
METALC_EXPORT char *ulltoa(unsigned long long value, char *str, int base);

#ifndef METALC_DISABLE_STDLIB_DEFS
#    define lldiv_t mclib_lldiv_t
#endif

cstdlib_export(llabs);
cstdlib_export(strtoll);
cstdlib_export(strtoull);
cstdlib_export(lldiv);
cstdlib_export(lltoa);
cstdlib_export(ulltoa);

#endif /* METALC_BITS_STDLIB_LONGLONG_H_ */
