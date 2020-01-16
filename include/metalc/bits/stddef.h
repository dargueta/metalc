#ifndef INCLUDE_METALC_BITS_STDDEF_H_
#define INCLUDE_METALC_BITS_STDDEF_H_

/* Since we're compiling this in strict ANSI C mode we don't have to worry about
 * our definition of ssize_t colliding with the compiler's *except* when we're
 * testing, when we need the host OS's C library as well. */

#if !defined METALC_DISABLE_STDLIB_DEFS || defined __STRICT_ANSI__
    #include <metalc/stdint.h>

    /* FIXME (dargueta): This is pretty specific to GCC and may not work on MinGW. */
    #if __SIZEOF_SIZE_T__ == 8
        typedef int64_t ssize_t;
    #elif __SIZEOF_SIZE_T__ == 4
        typedef int32_t ssize_t;
    #elif __SIZEOF_SIZE_T__ == 2
        typedef int16_t ssize_t;
    #else
        #error "Cannot define ssize_t: size_t width makes no sense: " ## __SIZEOF_SIZE_T__
    #endif
#endif  /* !METALC_DISABLE_STDLIB_DEFS */

#endif  /* INCLUDE_METALC_BITS_STDDEF_H_ */
