#ifndef INCLUDE_METALC_STDLIB_H_
#define INCLUDE_METALC_STDLIB_H_

#include "metalc.h"
#include "stddef.h"
#include "wchar.h"


#define RAND_MAX    INT_MAX

#ifndef NULL
    #define NULL ((void *)0)
#endif


typedef struct {
    int quot, rem;
} div_t;


typedef struct {
    long quot, rem;
} ldiv_t;


METALC_API_EXPORT_WITH_ATTR(nonnull, pure) double atof(const char *str);
METALC_API_EXPORT_WITH_ATTR(nonnull, pure) int atoi(const char *str);
METALC_API_EXPORT_WITH_ATTR(nonnull, pure) long atol(const char *str);
METALC_API_EXPORT_WITH_ATTR(nonnull(1)) long strtol(const char *str, const char **endptr, int base);
METALC_API_EXPORT_WITH_ATTR(nonnull(1)) unsigned long strtoul(const char *str, const char **endptr, int base);
METALC_API_EXPORT_WITH_ATTR(nonnull(1)) double strtod(const char *str, const char **endptr);
METALC_API_EXPORT_WITH_ATTR(noreturn) void abort(void);  /* done */
METALC_API_EXPORT_WITH_ATTR(nonnull) void atexit(void (*func)(void));
METALC_API_EXPORT_WITH_ATTR(noreturn) void exit(int status);
METALC_API_EXPORT_WITH_ATTR(nonnull, error("Function requires OS support.")) char *getenv(const char *name);
METALC_API_EXPORT_WITH_ATTR(nonnull, error("Function requires OS support.")) int system(const char *string);
METALC_API_EXPORT_WITH_ATTR(nonnull) void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*cmp)(const void *, const void *));
METALC_API_EXPORT_WITH_ATTR(nonnull) void qsort(void *base, size_t nitems, size_t size, int (*cmp)(const void *, const void *));
METALC_API_EXPORT_WITH_ATTR(const) int abs(int x);                        /* done */
METALC_API_EXPORT_WITH_ATTR(const) long labs(long x);                     /* done */
METALC_API_EXPORT_WITH_ATTR(const) div_t div(int numer, int denom);       /* done */
METALC_API_EXPORT_WITH_ATTR(const) ldiv_t ldiv(long numer, long denom);   /* done */
METALC_API_EXPORT int rand(void);
METALC_API_EXPORT void srand(unsigned seed);             /* done */
METALC_API_EXPORT_WITH_ATTR(pure) int mblen(const char *str, size_t n);
METALC_API_EXPORT size_t mbstowcs(wchar_t *pwcs, const char *str, size_t n);
METALC_API_EXPORT int mbtowc(wchar_t *pwc, const char *str, size_t n);
METALC_API_EXPORT size_t wcstombs(char *str, const wchar_t *pwcs, size_t n);
METALC_API_EXPORT int wctomb(char *str, wchar_t wchar);
METALC_API_EXPORT_WITH_ATTR(malloc, warn_unused_result) void *malloc(size_t size);
METALC_API_EXPORT_WITH_ATTR(malloc, warn_unused_result) void *calloc(size_t n_elements, size_t element_size);
METALC_API_EXPORT_WITH_ATTR(warn_unused_result) void *realloc(void *ptr, size_t size);
METALC_API_EXPORT void free(void *ptr);


#if METALC_HAVE_LONG_LONG
    #include "bits/stdlib_longlong.h"
#endif

/* Nonstandard functions */
METALC_API_EXPORT char *itoa(int value, char *str, int base);
METALC_API_EXPORT char *utoa(unsigned value, char *buf, int base);
METALC_API_EXPORT char *ltoa(long value, char *buf, int base);
METALC_API_EXPORT char *ultoa(unsigned long value, char *str, int base);

#endif  /* INCLUDE_METALC_STDLIB_H_ */
