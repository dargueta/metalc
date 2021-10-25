#ifndef INCLUDE_METALC_STDLIB_H_
#define INCLUDE_METALC_STDLIB_H_

#include "metalc.h"
#include "stddef.h"
#include "wchar.h"


#define mclib_RAND_MAX    INT_MAX


typedef struct {
    int quot, rem;
} mclib_div_t;


typedef struct {
    long quot, rem;
} mclib_ldiv_t;


#ifndef METALC_DISABLE_STDLIB_DEFS
    #define RAND_MAX mclib_RAND_MAX
    #define div_t mclib_div_t
    #define ldiv_t mclib_ldiv_t
#endif


double atof(const char *str);
int atoi(const char *str);
long atol(const char *str);
long strtol(const char *str, const char **endptr, int base);
unsigned long strtoul(const char *str, const char **endptr, int base);
double strtod(const char *str, const char **endptr);
void abort(void);
void atexit(void (*func)(void));
void exit(int status);
char *getenv(const char *name);
int system(const char *string);
void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*cmp)(const void *, const void *));
void qsort(void *base, size_t nitems, size_t size, int (*cmp)(const void *, const void *));
int abs(int x);
long labs(long x);
mclib_div_t div(int numer, int denom);
mclib_ldiv_t ldiv(long numer, long denom);
int rand(void);
void srand(unsigned seed);
int mblen(const char *str, size_t n);
size_t mbstowcs(mclib_wchar_t *pwcs, const char *str, size_t n);
int mbtowc(mclib_wchar_t *pwc, const char *str, size_t n);
size_t wcstombs(char *str, const mclib_wchar_t *pwcs, size_t n);
int wctomb(char *str, mclib_wchar_t wchar);
void *malloc(size_t size);
void *calloc(size_t n_elements, size_t element_size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);


cstdlib_export_with_attr(atof, nonnull, pure);
cstdlib_export_with_attr(atoi, nonnull, pure);
cstdlib_export_with_attr(atol, nonnull, pure);
cstdlib_export_with_attr(strtol, nonnull(1));
cstdlib_export_with_attr(strtoul, nonnull(1));
cstdlib_export_with_attr(strtod, nonnull(1));
cstdlib_export_with_attr(abort, noreturn);
cstdlib_export_with_attr(atexit, nonnull);
cstdlib_export_with_attr(exit, noreturn);
cstdlib_export_with_attr(getenv, nonnull, error("Function requires OS support."));
cstdlib_export_with_attr(system, nonnull, error("Function requires OS support."));
cstdlib_export(bsearch);
cstdlib_export(qsort);
cstdlib_export_with_attr(abs, const);
cstdlib_export_with_attr(labs, const);
cstdlib_export_with_attr(div, const);
cstdlib_export_with_attr(ldiv, const);
cstdlib_export(rand);
cstdlib_export(srand);
cstdlib_export_with_attr(mblen, pure);
cstdlib_export(mbstowcs);
cstdlib_export(mbtowc);
cstdlib_export(wcstombs);
cstdlib_export(wctomb);
cstdlib_export_with_attr(malloc, malloc, warn_unused_result);
cstdlib_export_with_attr(calloc, malloc, warn_unused_result);
cstdlib_export_with_attr(realloc, warn_unused_result);
cstdlib_export(free);


#if METALC_HAVE_LONG_LONG
    #include "bits/stdlib_longlong.h"
#endif

/* Nonstandard functions */
char *itoa(int value, char *str, int base);
char *utoa(unsigned value, char *buf, int base);
char *ltoa(long value, char *buf, int base);
char *ultoa(unsigned long value, char *str, int base);

cstdlib_export(itoa);
cstdlib_export(utoa);
cstdlib_export(ltoa);
cstdlib_export(ultoa);

#endif  /* INCLUDE_METALC_STDLIB_H_ */
