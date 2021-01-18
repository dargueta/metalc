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
} lldiv_t;


METALC_EXPORT_WITH_ATTR(const) long long llabs(long long x);      /* done */
METALC_EXPORT_WITH_ATTR(pure) long long atoll(const char *str);
METALC_EXPORT_WITH_ATTR(pure) long long strtoll(const char *str, const char **endptr, int base);
METALC_EXPORT_WITH_ATTR(pure) unsigned long long strtoull(const char *str, const char **endptr, int base);
METALC_EXPORT_WITH_ATTR(const) lldiv_t lldiv(long long numer, long long denom);

/* Nonstandard */
METALC_EXPORT char *lltoa(long long value, char *buf, int base);
METALC_EXPORT char *ulltoa(unsigned long long value, char *str, int base);

#endif  /* METALC_BITS_STDLIB_LONGLONG_H_ */
