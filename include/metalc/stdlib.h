#ifndef INCLUDE_METALC_STDLIB_H_
#define INCLUDE_METALC_STDLIB_H_

#include <limits.h>
#include <stddef.h>

#include <metalc/metalc.h>


#define __mcapi_RAND_MAX    INT_MAX


typedef struct {
    int quot, rem;
} __mcapi_div_t;


typedef struct {
    long quot, rem;
} __mcapi_ldiv_t;


METALC_API_EXPORT double __mcapi_atof(const char *str);
METALC_API_EXPORT int __mcapi_atoi(const char *str);
METALC_API_EXPORT long __mcapi_atol(const char *str);
METALC_API_EXPORT long __mcapi_strtol(const char *str, const char **endptr, int base);
METALC_API_EXPORT unsigned long __mcapi_strtoul(const char *str, const char **endptr, int base);
METALC_API_EXPORT double __mcapi_strtod(const char *str, const char **endptr);
METALC_API_EXPORT void __mcapi_abort(void);  /* done */
METALC_API_EXPORT void __mcapi_atexit(void (*func)(void));
METALC_API_EXPORT void __mcapi_exit(int status);
METALC_API_EXPORT char *__mcapi_getenv(const char *name);
METALC_API_EXPORT int __mcapi_system(const char *string);
METALC_API_EXPORT void *__mcapi_bsearch(
    const void *key,
    const void *base,
    size_t nitems,
    size_t size,
    int (*cmp)(const void *, const void *)
);
METALC_API_EXPORT void __mcapi_qsort(
    void *base,
    size_t nitems,
    size_t size,
    int (*cmp)(const void *, const void *)
);
METALC_API_EXPORT int __mcapi_abs(int x);                        /* done */
METALC_API_EXPORT long __mcapi_labs(long x);                     /* done */
METALC_API_EXPORT __mcapi_div_t __mcapi_div(int numer, int denom);       /* done */
METALC_API_EXPORT __mcapi_ldiv_t __mcapi_ldiv(long numer, long denom);   /* done */
METALC_API_EXPORT int __mcapi_rand(void);
METALC_API_EXPORT void __mcapi_srand(unsigned seed);             /* done */
METALC_API_EXPORT int __mcapi_mblen(const char *str, size_t n);
METALC_API_EXPORT size_t __mcapi_mbstowcs(wchar_t *pwcs, const char *str, size_t n);
METALC_API_EXPORT int __mcapi_mbtowc(wchar_t *pwc, const char *str, size_t n);
METALC_API_EXPORT size_t __mcapi_wcstombs(char *str, const wchar_t *pwcs, size_t n);
METALC_API_EXPORT int __mcapi_wctomb(char *str, wchar_t wchar);

METALC_API_EXPORT void *__mcapi_malloc(size_t size);
METALC_API_EXPORT void *__mcapi_calloc(size_t n_elements, size_t element_size);
METALC_API_EXPORT void *__mcapi_realloc(void *ptr, size_t size);
METALC_API_EXPORT void __mcapi_free(void *ptr);


#if METALC_HAVE_LONG_LONG
    typedef struct {
        long long quot, rem;
    } __mcapi_lldiv_t;

    METALC_API_EXPORT long long __mcapi_llabs(long long x);      /* done */
    METALC_API_EXPORT long long __mcapi_atoll(const char *str);
    METALC_API_EXPORT long long __mcapi_strtoll(const char *str, const char **endptr, int base);
    METALC_API_EXPORT unsigned long long __mcapi_strtoull(const char *str, const char **endptr, int base);
    METALC_API_EXPORT __mcapi_lldiv_t __mcapi_lldiv(long long numer, long long denom);

    /* Nonstandard */
    METALC_API_EXPORT char *__mcapi_lltoa(long long value, char *buf, int base);
    METALC_API_EXPORT char *__mcapi_ulltoa(unsigned long long value, char *str, int base);
#endif

/* Nonstandard functions */
METALC_API_EXPORT char *__mcapi_itoa(int value, char *str, int base);
METALC_API_EXPORT char *__mcapi_utoa(unsigned value, char *buf, int base);
METALC_API_EXPORT char *__mcapi_ltoa(long value, char *buf, int base);
METALC_API_EXPORT char *__mcapi_ultoa(unsigned long value, char *str, int base);

#endif  /* INCLUDE_METALC_STDLIB_H_ */
