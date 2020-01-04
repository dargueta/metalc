#ifndef INCLUDE_METALC_STDINT_H_
#define INCLUDE_METALC_STDINT_H_

#include <metalc/metalc.h>


#if METALC_HAVE_STDINT_H
    /* Always defer to the platform's header file if present. GCC-compatible
     * compilers will provide this for us. */
    #include <stdint.h>
#elif METALC_COMPILER_MS_COMPATIBLE
    /* No stdint.h but Microsoft-compatible compilers provide some non-standard
     * predefined types for us. */
    typedef __int8 int8_t;
    typedef __int16 int16_t;
    typedef __int32 int32_t;
    typedef __int64 int64_t;
    typedef unsigned __int8 uint8_t;
    typedef unsigned __int16 uint16_t;
    typedef unsigned __int32 uint32_t;
    typedef unsigned __int64 uint64_t;
    typedef int int_least8_t;
    typedef int int_least16_t;
    typedef int int_least32_t;
    typedef int64_t int_least64_t;
    typedef unsigned int uint_least8_t;
    typedef unsigned int uint_least16_t;
    typedef unsigned int uint_least32_t;
    typedef uint64_t uint_least64_t;
#elif METALC_HAVE_LIMITS_H
    /* We don't have stdint.h and no predefined sized types, so we gotta figure
     * it out ourselves. */
    #include <limits.h>

    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef int8_t int_least8_t;
    typedef uint8_t uint_least8_t;

    #if USHRT_MAX == 65535
        typedef short int16_t;
        typedef unsigned short uint16_t;
        typedef int16_t int_least16_t;
        typedef uint16_t uint_least16_t;
    #else
        #error "A `short` isn't 16 bits, don't know how to typedef a 16-bit integer."
    #endif

    #if UINT_MAX < 4294967295UL
        /* `int` is 16 bits, so `long` must be 32...right? */
        #define INT_IS_16_BITS
        #if ULONG_MAX == 4294967295UL
            /* int is 16 bits, long is 32 bits */
            typedef long int32_t;
            typedef unsigned long uint32_t;
            typedef int32_t int_least32_t;
            typedef uint32_t uint_least32_t;
        #else
            #error "`int` is 16 bits, `long` isn't 32 bits, not sure how to define a 32-bit integer."
        #endif
    #elif UINT_MAX == 4294967295UL
        typedef int int32_t;
        typedef unsigned int uint32_t;
        typedef int32_t int_least32_t;
        typedef uint32_t uint_least32_t;
    #elif UINT_MAX > 4294967295UL
        #error "An `int` is more than 32 bits, don't know how to typedef a 32-bit integer."
    #endif

    #if ULONG_MAX > UINT_MAX
        /* A long is bigger than an int. */
        #ifdef INT_IS_16_BITS
            /* Long is 32 bits, need a `long long` for 64-bit integers. */
            #ifdef ULLONG_MAX
                /* `long long` supported; by definition it's at least 64 bits. */
                typedef long long int64_t;
                typedef unsigned long long uint64_t;
                typedef int64_t int_least64_t;
                typedef uint64_t uint_least64_t;
            #else
                #error "Can't define a 64-bit integer: `long` is 32 bits and compiler doesn't support `long long`"
            #endif
        #else
            /* `long` is bigger than an `int` and an `int` is 32 bits, thus a
             * `long` is (probably) 64 bits. */
            typedef long int64_t;
            typedef unsigned long uint64_t;
            typedef int64_t int_least64_t;
            typedef uint64_t uint_least64_t;
        #endif
    #else
        /* A long is the same size as an int. If the compiler defines `long long`
         * then that must be our 64-bit integer. */
        #if defined ULLONG_MAX
            typedef long long int64_t;
            typedef unsigned long long uint64_t;
            typedef int64_t int_least64_t;
            typedef uint64_t uint_least64_t;
        #else
            #error "Can't define a 64-bit integer: `long` is the same size as `int` and compiler doesn't support `long long`"
        #endif
    #endif
#else
    #error "Can't determine integer sizes; compiler doesn't provide limits.h."
#endif

#ifdef INT_IS_16_BITS
    #undef INT_IS_16_BITS
#endif

#endif  /* INCLUDE_METALC_STDINT_H_ */
