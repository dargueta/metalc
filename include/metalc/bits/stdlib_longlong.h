#ifndef METALC_BITS_STDLIB_LONGLONG_H_
#define METALC_BITS_STDLIB_LONGLONG_H_

#include <metalc/metalc.h>


typedef struct {
    long long quot, rem;
} __mcapi_lldiv_t;

long long llabs(long long x);      /* done */
long long atoll(const char *str);
long long strtoll(const char *str, const char **endptr, int base);
unsigned long long strtoull(const char *str, const char **endptr, int base);
__mcapi_lldiv_t lldiv(long long numer, long long denom);

/* Nonstandard */
char *lltoa(long long value, char *buf, int base);
char *ulltoa(unsigned long long value, char *str, int base);

cstdlib_export_with_attr(llabs, const);
cstdlib_export_with_attr(atoll, pure);
cstdlib_export_with_attr(strtoll, pure);
cstdlib_export_with_attr(strtoull, pure);
cstdlib_export_with_attr(lldiv, const);
cstdlib_export(lltoa);
cstdlib_export(ulltoa);

#endif  /* METALC_BITS_STDLIB_LONGLONG_H_ */
