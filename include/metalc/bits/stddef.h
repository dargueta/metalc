#ifndef INCLUDE_METALC_BITS_STDDEF_H_
#define INCLUDE_METALC_BITS_STDDEF_H_

/* Since we're compiling this in strict ANSI C mode we don't have to worry about
 * our definition of ssize_t colliding with the compiler's *except* when we're
 * testing, when we need the host OS's C library as well. */

#if !defined METALC_DISABLE_STDLIB_DEFS || defined __STRICT_ANSI__
    #include "../stdint.h"

    typedef uintptr_t size_t;
    typedef intptr_t ssize_t;

    #define SIZE_MAX UINTPTR_MAX
    #define SSIZE_MIN INTPTR_MIN
    #define SSIZE_MAX INTPTR_MAX

#endif  /* !METALC_DISABLE_STDLIB_DEFS */

#endif  /* INCLUDE_METALC_BITS_STDDEF_H_ */
