#ifndef INCLUDE_METALC_STDLIB_H_
#define INCLUDE_METALC_STDLIB_H_

#include <limits.h>
#include <stddef.h>

#include <metalc/metalc.h>


#define RAND_MAX    INT_MAX


typedef struct {
    int quot, rem;
} div_t;


typedef struct {
    long quot, rem;
} ldiv_t;


METALC_API_EXPORT double atof(const char *str);
METALC_API_EXPORT int atoi(const char *str);
METALC_API_EXPORT long atol(const char *str);
METALC_API_EXPORT char *itoa(int value, char *str, int base);
METALC_API_EXPORT long strtol(const char *str, const char **endptr, int base);
METALC_API_EXPORT unsigned long strtoul(const char *str, const char **endptr, int base);
METALC_API_EXPORT double strtod(const char *str, const char **endptr);
METALC_API_EXPORT_WITH_ATTR(noreturn) void abort(void);  /* done */
METALC_API_EXPORT void atexit(void (*func)(void));
METALC_API_EXPORT_WITH_ATTR(noreturn) void exit(int status);
METALC_API_EXPORT_WITH_ATTR(warning ("Requires underlying OS support")) char *getenv(const char *name);
METALC_API_EXPORT_WITH_ATTR(warning ("Requires underlying OS support")) int system(const char *string);
METALC_API_EXPORT void *bsearch(
    const void *key,
    const void *base,
    size_t nitems,
    size_t size,
    int (*cmp)(const void *, const void *)
);
METALC_API_EXPORT void qsort(
    void *base,
    size_t nitems,
    size_t size,
    int (*cmp)(const void *, const void *)
);
METALC_API_EXPORT int abs(int x);                        /* done */
METALC_API_EXPORT long labs(long x);                     /* done */
METALC_API_EXPORT div_t div(int numer, int denom);       /* done */
METALC_API_EXPORT ldiv_t ldiv(long numer, long denom);   /* done */
METALC_API_EXPORT int rand(void);
METALC_API_EXPORT void srand(unsigned seed);             /* done */
METALC_API_EXPORT int mblen(const char *str, size_t n);
METALC_API_EXPORT size_t mbstowcs(wchar_t *pwcs, const char *str, size_t n);
METALC_API_EXPORT int mbtowc(wchar_t *pwc, const char *str, size_t n);
METALC_API_EXPORT size_t wcstombs(char *str, const wchar_t *pwcs, size_t n);
METALC_API_EXPORT int wctomb(char *str, wchar_t wchar);

METALC_API_EXPORT void *malloc(size_t size);
METALC_API_EXPORT void *calloc(size_t n_elements, size_t element_size);
METALC_API_EXPORT void *realloc(void *ptr, size_t size);
METALC_API_EXPORT void free(void *ptr);


#if METALC_HAVE_LONG_LONG
    typedef struct {
        long long quot, rem;
    } lldiv_t;

    METALC_API_EXPORT long long llabs(long long x);      /* done */
    METALC_API_EXPORT long long atoll(const char *str);
    METALC_API_EXPORT long long strtoll(const char *str, const char **endptr, int base);
    METALC_API_EXPORT unsigned long long strtoull(const char *str, const char **endptr, int base);
    METALC_API_EXPORT lldiv_t lldiv(long long numer, long long denom);
#endif

/* Nonstandard functions */
METALC_API_EXPORT char *utoa(unsigned value, char *buf, int base);
METALC_API_EXPORT char *ltoa(long value, char *buf, int base);
METALC_API_EXPORT char *ultoa(unsigned long value, char *str, int base);

#endif  /* INCLUDE_METALC_STDLIB_H_ */
