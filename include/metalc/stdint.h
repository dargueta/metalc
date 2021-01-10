#ifndef INCLUDE_METALC_STDINT_H_
#define INCLUDE_METALC_STDINT_H_

#include "metalc.h"


#if METALC_HAVE_STDINT_H
    /* Always defer to the platform's header file if present. GCC-compatible
     * compilers will provide this for us. In the past I've had trouble getting
     * it to work with Visual Studio so I have a backup plan below. */
    #include <stdint.h>
#elif METALC_HAVE_LIMITS_H
    /* We don't have stdint.h so we gotta figure it out ourselves. */
    #include <limits.h>

    typedef signed char int_least8_t;
    typedef unsigned char uint_least8_t;

    #define INT_LEAST8_MIN      SCHAR_MIN
    #define INT_LEAST8_MAX      SCHAR_MAX
    #define UINT_LEAST8_MAX     UCHAR_MAX

    typedef signed short int_least16_t;
    typedef unsigned short uint_least16_t;

    #define INT_LEAST16_MIN     SHRT_MIN
    #define INT_LEAST16_MAX     SHRT_MAX
    #define UINT_LEAST16_MAX    USHRT_MAX

    #if SHRT_MAX >= 0x7FFFFFFF
        /* A short is at least 32 bits. This is rare but it does happen in some
         * specialized systems. */
        typedef signed short int_least32_t;
        typedef unsigned short uint_least32_t;

        #define INT_LEAST32_MIN     SHRT_MIN
        #define INT_LEAST32_MAX     SHRT_MAX
        #define UINT_LEAST32_MAX    USHRT_MAX
    #elif INT_MAX >= 0x7FFFFFFF
        /* Int is at least 32 bits */
        typedef signed int int_least32_t;
        typedef unsigned int uint_least32_t;

        #define INT_LEAST32_MIN     INT_MIN
        #define INT_LEAST32_MAX     INT_MAX
        #define UINT_LEAST32_MAX    UINT_MAX
    #else
        /* Int is the same size as a short (probably 16 bits), which means we
         * must use a long for 32 bits. */
        typedef signed long int_least32_t;
        typedef unsigned long uint_least32_t;

        #define INT_LEAST32_MIN     LONG_MIN
        #define INT_LEAST32_MAX     LONG_MAX
        #define UINT_LEAST32_MAX    ULONG_MAX
    #endif

    #if INT_MAX > 0x7FFFFFFF
        /* An int is greater than 32 bits. Rare, but again, it does happen. It
         * is VERY unlikely nowadays that this will be anything but 64 bits, so
         * we're going to take a gamble. */
        typedef signed int int_least64_t;
        typedef unsigned int uint_least64_t;

        #define INT_LEAST64_MIN     INT_MIN
        #define INT_LEAST64_MAX     INT_MAX
        #define UINT_LEAST64_MAX    UINT_MAX
    #elif LONG_MAX > 0x7FFFFFFF
        /* `long` is greater than 32 bits, assume it's 64. */
        typedef signed long int_least64_t;
        typedef unsigned long uint_least64_t;

        #define INT_LEAST64_MIN     LONG_MIN
        #define INT_LEAST64_MAX     LONG_MAX
        #define UINT_LEAST64_MAX    ULONG_MAX
    #elif defined(LLONG_MAX)
        /* Compiler defines a `long long` which by definition must be at least
         * 64 bits. */
        typedef signed long long int_least64_t;
        typedef unsigned long long uint_least64_t;

        #define INT_LEAST64_MIN     LLONG_MIN
        #define INT_LEAST64_MAX     LLONG_MAX
        #define UINT_LEAST64_MAX    ULLONG_MAX
    /* else: No way to define a 64-bit integer. We're probably compiling for a
     * 16-bit system. */
    #endif

    #if METALC_ARCH_BITS == 16
        typedef int_least16_t intptr_t;
        typedef uint_least16_t uintptr_t;
        typedef int_least16_t ptrdiff_t;

        #define INTPTR_MIN  INT_LEAST16_MIN
        #define INTPTR_MAX  INT_LEAST16_MAX
        #define UINTPTR_MAX UINT_LEAST16_MAX
    #elif METALC_ARCH_BITS == 32
        typedef int_least32_t intptr_t;
        typedef uint_least32_t uintptr_t;
        typedef int_least32_t ptrdiff_t;

        #define INTPTR_MIN  INT_LEAST32_MIN
        #define INTPTR_MAX  INT_LEAST32_MAX
        #define UINTPTR_MAX UINT_LEAST32_MAX
    #else   /* METALC_ARCH_BITS == 64 */
        typedef int_least64_t intptr_t;
        typedef uint_least64_t uintptr_t;
        typedef int_least64_t ptrdiff_t;

        #define INTPTR_MIN  INT_LEAST64_MIN
        #define INTPTR_MAX  INT_LEAST64_MAX
        #define UINTPTR_MAX UINT_LEAST64_MAX
    #endif

    /* This won't be accurate for systems that support integers greater than 64
     * bits, but it's good enough... right? */
    #if defined(INT_LEAST64_MAX)
        typedef int_least64_t intmax_t;
        typedef uint_least64_t uintmax_t;

        #define INTMAX_MIN  INT_LEAST64_MIN
        #define INTMAX_MAX  INT_LEAST64_MAX
        #define UINTMAX_MAX UINT_LEAST64_MAX
    #elif defined(INT_LEAST32_MAX)
        typedef int_least32_t intmax_t;
        typedef uint_least32_t uintmax_t;

        #define INTMAX_MIN  INT_LEAST32_MIN
        #define INTMAX_MAX  INT_LEAST32_MAX
        #define UINTMAX_MAX UINT_LEAST32_MAX
    #else
        /* Super unlikely but theoretically possible, e.g. if you're compiling
         * for a z80 or something (which we don't have support for yet). */
        typedef int_least16_t intmax_t;
        typedef uint_least16_t uintmax_t;

        #define INTMAX_MIN  INT_LEAST16_MIN
        #define INTMAX_MAX  INT_LEAST16_MAX
        #define UINTMAX_MAX UINT_LEAST16_MAX
    #endif

    #if UCHAR_MAX == 255
        typedef unsigned char uint8_t;
        typedef signed char int8_t;
        #define UINT8_MAX   255
        #define INT8_MIN    -127
        #define INT8_MAX    127
    #endif

    #if USHRT_MAX == 65535
        typedef unsigned short uint16_t;
        typedef signed short int16_t;
        #define UINT16_MAX  65535
        #define INT16_MIN   -32767
        #define INT16_MAX   32767
    #endif

    #if defined(UINT_LEAST32_MAX) && UINT_LEAST32_MAX == 0xFFFFFFFF
        typedef uint_least32_t uint32_t;
        typedef int_least32_t int32_t;
        #define UINT32_MAX  0xFFFFFFFF
        #define INT32_MIN   -0x7FFFFFFF
        #define INT32_MAX   0x7FFFFFFF
    #endif

    #if defined(UINT_LEAST64_MAX) && UINT_LEAST64_MAX == 0xFFFFFFFFFFFFFFFF
        typedef uint_least64_t uint64_t;
        typedef int_least64_t int64_t;
        #define UINT64_MAX  0xFFFFFFFFFFFFFFFF
        #define INT64_MIN   -0x7FFFFFFFFFFFFFFF
        #define INT64_MAX   0x7FFFFFFFFFFFFFFF
    #endif

    /* We're not going to define int_fast*_t because we don't know enough about
     * the hardware. */
#else
    /* This should never happen */
    #error Can't determine integer sizes; compiler doesn't provide limits.h.
#endif

#endif  /* INCLUDE_METALC_STDINT_H_ */
