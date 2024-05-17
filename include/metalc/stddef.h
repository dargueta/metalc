#ifndef INCLUDE_METALC_STDDEF_H_
#define INCLUDE_METALC_STDDEF_H_

#include "internal/poison.h"
#include "metalc.h"
#include "stdint.h"

#ifdef METALC_CURRENTLY_COMPILING_LIBRARY
#    define mclib_NULL ((void *)0)
#else
#    define NULL ((void *)0)
#endif

// Why we use `long double` https://en.cppreference.com/w/c/types/max_align_t
#ifndef METALC_MAX_ALIGN_T_DEFINED
#    if METALC_HAVE_LONG_DOUBLE
typedef long double LIBC_GUARD(max_align_t);
#    else
typedef intmax_t LIBC_GUARD(max_align_t);
#    endif
#    define METALC_MAX_ALIGN_T_DEFINED
#endif

typedef uintptr_t LIBC_GUARD(size_t);
typedef intptr_t LIBC_GUARD(ssize_t);

#define mclib_SIZE_MAX UINTPTR_MAX
#define mclib_SSIZE_MIN INTPTR_MIN
#define mclib_SSIZE_MAX INTPTR_MAX

#ifndef METALC_DISABLE_STDLIB_DEFS
#    define NULL mclib_NULL
#    define max_align_t mclib_max_align_t
#    define SIZE_MAX mclib_SIZE_MAX
#    define SSIZE_MIN mclib_SSIZE_MIN
#    define SSIZE_MAX mclib_SSIZE_MAX
#endif

#ifdef __has_builtin
#    if __has_builtin(__builtin_offsetof)
#        define offsetof(type, member) __builtin_offsetof(type, member)
#    endif
#endif

#ifndef offsetof
#    define offsetof(type, member) ((mclib_size_t)(&(((type *)0)->member)))
#endif

#endif // INCLUDE_METALC_STDDEF_H_
