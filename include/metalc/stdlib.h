#ifndef INCLUDE_METALC_STDLIB_H_
#define INCLUDE_METALC_STDLIB_H_

#include "metalc.h"
#include "stddef.h"
#include "wchar.h"

#define mclib_RAND_MAX INT_MAX

typedef struct
{
    int quot, rem;
} mclib_div_t;

typedef struct
{
    long quot, rem;
} mclib_ldiv_t;

#ifndef METALC_DISABLE_STDLIB_DEFS
#    define RAND_MAX mclib_RAND_MAX
#    define div_t mclib_div_t
#    define ldiv_t mclib_ldiv_t
#endif

#define atoi(str) ((int)strtol((str), NULL, 10))
#define atol(str) strtol((str), NULL, 10)

METALC_EXPORT
METALC_ATTR__NONNULL
double atof(const char *str);

METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(1)
long strtol(const char *str, const char **endptr, int base);

METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(1)
unsigned long strtoul(const char *str, const char **endptr, int base);

METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(1)
double strtod(const char *str, const char **endptr);

METALC_EXPORT
METALC_ATTR__NORETURN
void abort(void);

METALC_EXPORT
METALC_ATTR__NONNULL
void atexit(void (*func)(void));

METALC_EXPORT
METALC_ATTR__NORETURN
void exit(int status);

METALC_EXPORT
METALC_ATTR__NONNULL
METALC_ATTR__ERROR_IF_USED("Function requires OS support.")
char *getenv(const char *name);

METALC_EXPORT
METALC_ATTR__NONNULL
METALC_ATTR__ERROR_IF_USED("Function requires OS support.")
int system(const char *string);

METALC_EXPORT
METALC_ATTR__NONNULL
void *bsearch(const void *key, const void *base, mclib_size_t nitems, mclib_size_t size,
              int (*cmp)(const void *, const void *));

METALC_EXPORT
void qsort(void *base, mclib_size_t nitems, mclib_size_t size,
           int (*cmp)(const void *, const void *));

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int abs(int x);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
long labs(long x);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
mclib_div_t div(int numer, int denom);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
mclib_ldiv_t ldiv(long numer, long denom);

METALC_EXPORT
int rand(void);

METALC_EXPORT
void srand(unsigned seed);

METALC_EXPORT
int mblen(const char *str, mclib_size_t n);

METALC_EXPORT
mclib_size_t mbstowcs(mclib_wchar_t *pwcs, const char *str, mclib_size_t n);

METALC_EXPORT
int mbtowc(mclib_wchar_t *pwc, const char *str, mclib_size_t n);

METALC_EXPORT
mclib_size_t wcstombs(char *str, const mclib_wchar_t *pwcs, mclib_size_t n);

METALC_EXPORT
int wctomb(char *str, mclib_wchar_t wchar);

METALC_EXPORT
void free(void *ptr);

METALC_EXPORT
METALC_ATTR__NODISCARD
METALC_ATTR__MALLOC_ARGS(free)
void *malloc(mclib_size_t size);

METALC_EXPORT
METALC_ATTR__NODISCARD
METALC_ATTR__MALLOC_ARGS(free)
void *calloc(mclib_size_t n_elements, mclib_size_t element_size);

METALC_EXPORT
METALC_ATTR__NODISCARD
void *realloc(void *ptr, mclib_size_t size);

cstdlib_export(atof);
cstdlib_export(strtol);
cstdlib_export(strtoul);
cstdlib_export(strtod);
cstdlib_export(abort);
cstdlib_export(atexit);
cstdlib_export(exit);
cstdlib_export(getenv);
cstdlib_export(system);
cstdlib_export(bsearch);
cstdlib_export(qsort);
cstdlib_export(abs);
cstdlib_export(labs);
cstdlib_export(div);
cstdlib_export(ldiv);
cstdlib_export(rand);
cstdlib_export(srand);
cstdlib_export(mblen);
cstdlib_export(mbstowcs);
cstdlib_export(mbtowc);
cstdlib_export(wcstombs);
cstdlib_export(wctomb);
cstdlib_export(malloc);
cstdlib_export(calloc);
cstdlib_export(realloc);
cstdlib_export(free);

#if METALC_HAVE_LONG_LONG
#    include "bits/stdlib_longlong.h"
#endif

/* Nonstandard functions */
METALC_EXPORT char *itoa(int value, char *str, int base);
METALC_EXPORT char *utoa(unsigned value, char *buf, int base);
METALC_EXPORT char *ltoa(long value, char *buf, int base);
METALC_EXPORT char *ultoa(unsigned long value, char *str, int base);

cstdlib_export(itoa);
cstdlib_export(utoa);
cstdlib_export(ltoa);
cstdlib_export(ultoa);

#endif /* INCLUDE_METALC_STDLIB_H_ */
