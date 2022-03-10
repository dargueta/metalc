/**
 * Definitions of sized integers.
 *
 * @file stdint.h
 */

#ifndef INCLUDE_METALC_STDINT_H_
#define INCLUDE_METALC_STDINT_H_

#include <limits.h>     /* Provided by the compiler */


typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;

#define INT_LEAST8_MIN      SCHAR_MIN
#define INT_LEAST8_MAX      SCHAR_MAX
#define UINT_LEAST8_MAX     UCHAR_MAX

#if SCHAR_MAX >= 32767
    /* Unlikely, but theoretically a char could be >= 16 bits. */
    typedef signed char int_least16_t;
    typedef unsigned char uint_least16_t;

    #define INT_LEAST16_MIN     SCHAR_MIN
    #define INT_LEAST16_MAX     SCHAR_MAX
    #define UINT_LEAST16_MAX    UCHAR_MAX
#else
    /* A short is defined by the standard to be at least 16 bits. */
    typedef signed short int_least16_t;
    typedef unsigned short uint_least16_t;

    #define INT_LEAST16_MIN     SHRT_MIN
    #define INT_LEAST16_MAX     SHRT_MAX
    #define UINT_LEAST16_MAX    USHRT_MAX
#endif

#if SHRT_MAX >= 0x7FFFFFFF
    /* A short is at least 32 bits here. This is rare but it does happen in some
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
    /* Int is the same size as a short (probably 16 bits), which means we must
     * use a long for 32 bits. */
    typedef signed long int_least32_t;
    typedef unsigned long uint_least32_t;

    #define INT_LEAST32_MIN     LONG_MIN
    #define INT_LEAST32_MAX     LONG_MAX
    #define UINT_LEAST32_MAX    ULONG_MAX
#endif

#if SHRT_MAX >= 0x7FFFFFFFFFFFFFFFLL
    /* According to Wikipedia some systems actually do have 64-bit shorts. I'm
     * not doing this for fun. */
    typedef signed short int_least64_t;
    typedef unsigned short uint_least64_t;

    #define INT_LEAST64_MIN     SHRT_MIN
    #define INT_LEAST64_MAX     SHRT_MAX
    #define UINT_LEAST64_MAX    USHRT_MAX
#elif INT_MAX >= 0x7FFFFFFFFFFFFFFFLL
    /* An int is at least 64 bits. Rare, but again, it does happen. */
    typedef signed int int_least64_t;
    typedef unsigned int uint_least64_t;

    #define INT_LEAST64_MIN     INT_MIN
    #define INT_LEAST64_MAX     INT_MAX
    #define UINT_LEAST64_MAX    UINT_MAX
#elif LONG_MAX >= 0x7FFFFFFFFFFFFFFFLL
    /* `long` is at least 64 bits. */
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
/* else: No way to define a 64-bit integer. Weird nowadays, but possible. */
#endif


#if INT_LEAST8_MAX == 127
    typedef uint_least8_t uint8_t;
    typedef int_least8_t int8_t;
    #define HAVE_INT8
#elif defined(_MSC_VER)
    /* Microsoft */
    typedef unsigned __int8 uint8_t;
    typedef signed __int8 int8_t;
    #define HAVE_INT8
#elif defined(__INT8_TYPE__)
    /* GCC */
    typedef __UINT8_TYPE__  uint8_t;
    typedef __INT8_TYPE__ int8_t;
    #define HAVE_INT8
#endif

#ifdef HAVE_INT8
    #define UINT8_MAX   (255U)
    #define INT8_MIN    (-127)
    #define INT8_MAX    (127)
    #undef HAVE_INT8
#endif


#if INT_LEAST16_MAX == 32767
    typedef uint_least16_t uint16_t;
    typedef int_least16_t int16_t;
    #define HAVE_INT16
#elif defined(_MSC_VER)
    /* Microsoft */
    typedef unsigned __int16 uint16_t;
    typedef signed __int16 int16_t;
    #define HAVE_INT16
#elif defined(__INT16_TYPE__)
    /* GCC */
    typedef __UINT16_TYPE__  uint16_t;
    typedef __INT16_TYPE__ int16_t;
    #define HAVE_INT16
#endif

#ifdef HAVE_INT16
    #define UINT16_MAX  (65535U)
    #define INT16_MIN   (-32767)
    #define INT16_MAX   (32767)
    #undef HAVE_INT16
#endif


#if defined(INT_LEAST32_MAX) && (INT_LEAST32_MAX == 0x7FFFFFFFL)
    typedef uint_least32_t uint32_t;
    typedef int_least32_t int32_t;
    #define HAVE_INT32
#elif defined(_MSC_VER)
    /* Microsoft */
    typedef unsigned __int32 uint32_t;
    typedef signed __int32 int32_t;
    #define HAVE_INT32
#elif defined(__INT32_TYPE__)
    /* GCC */
    typedef __UINT32_TYPE__  uint32_t;
    typedef __INT32_TYPE__ int32_t;
    #define HAVE_INT32
#endif

#ifdef HAVE_INT32
    #define UINT32_MAX  (0xFFFFFFFFU)
    #define INT32_MIN   (-0x7FFFFFFF)
    #define INT32_MAX   (0x7FFFFFFF)
    #undef HAVE_INT32
#endif


#if defined(INT_LEAST64_MAX) && (INT_LEAST64_MAX == 0x7FFFFFFFFFFFFFFFLL)
    typedef uint_least64_t uint64_t;
    typedef int_least64_t int64_t;
    #define HAVE_INT64
#elif defined(_MSC_VER)
    /* Microsoft */
    typedef unsigned __int64 uint64_t;
    typedef signed __int64 int64_t;
    #define HAVE_INT64
#elif defined(__INT64_TYPE__)
    /* GCC */
    typedef __UINT64_TYPE__  uint64_t;
    typedef __INT64_TYPE__ int64_t;
    #define HAVE_INT64
#endif

#ifdef HAVE_INT64
    #define UINT64_MAX  (0xFFFFFFFFFFFFFFFFULL)
    #define INT64_MIN   (-0x7FFFFFFFFFFFFFFFLL)
    #define INT64_MAX   (0x7FFFFFFFFFFFFFFFLL)
    #undef HAVE_INT64
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
#elif METALC_ARCH_BITS == 64
    typedef int_least64_t intptr_t;
    typedef uint_least64_t uintptr_t;
    typedef int_least64_t ptrdiff_t;

    #define INTPTR_MIN  INT_LEAST64_MIN
    #define INTPTR_MAX  INT_LEAST64_MAX
    #define UINTPTR_MAX UINT_LEAST64_MAX
#endif


/* This won't be accurate for systems that support integers greater than 64
 * bits, but it's good enough... right? */
#if (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS == 64) || defined(INT_LEAST64_MAX)
    typedef int_least64_t intmax_t;
    typedef uint_least64_t uintmax_t;

    #define INTMAX_MIN  INT_LEAST64_MIN
    #define INTMAX_MAX  INT_LEAST64_MAX
    #define UINTMAX_MAX UINT_LEAST64_MAX
#elif (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS == 32) || defined(INT_LEAST32_MAX)
    typedef int_least32_t intmax_t;
    typedef uint_least32_t uintmax_t;

    #define INTMAX_MIN  INT_LEAST32_MIN
    #define INTMAX_MAX  INT_LEAST32_MAX
    #define UINTMAX_MAX UINT_LEAST32_MAX
#else
    /* Super unlikely but theoretically possible, e.g. if you're compiling for a
     * z80 or something (which we don't have support for yet). */
    typedef int_least16_t intmax_t;
    typedef uint_least16_t uintmax_t;

    #define INTMAX_MIN  INT_LEAST16_MIN
    #define INTMAX_MAX  INT_LEAST16_MAX
    #define UINTMAX_MAX UINT_LEAST16_MAX
#endif

/* GCC and some compatible compilers define macros that expand to the C types
 * with the attributes we need. Since we have no idea of the underlying hardware,
 * we need to rely on these to be able to define the int_fast*_t types. */

#if defined(__INT_FAST8_TYPE__)
    typedef __INT_FAST8_TYPE__ int_fast8_t;
    typedef __UINT_FAST8_TYPE__ uint_fast8_t;
    #define INT_FAST8_MAX __UINT_FAST8_MAX__
    #define INT_FAST8_MIN __UINT_FAST8_MIN__
    #define UINT_FAST8_MAX __UINT_FAST8_MAX__
#endif

#if defined(__INT_FAST16_TYPE__)
    typedef __INT_FAST16_TYPE__ int_fast16_t;
    typedef __UINT_FAST16_TYPE__ uint_fast16_t;
    #define INT_FAST16_MAX __UINT_FAST16_MAX__
    #define INT_FAST16_MIN __UINT_FAST16_MIN__
    #define UINT_FAST16_MAX __UINT_FAST16_MAX__
#endif

#if defined(__INT_FAST32_TYPE__)
    typedef __INT_FAST32_TYPE__ int_fast32_t;
    typedef __UINT_FAST32_TYPE__ uint_fast32_t;
    #define INT_FAST32_MAX __UINT_FAST32_MAX__
    #define INT_FAST32_MIN __UINT_FAST32_MIN__
    #define UINT_FAST32_MAX __UINT_FAST32_MAX__
#endif

#if defined(__INT_FAST64_TYPE__)
    typedef __INT_FAST64_TYPE__ int_fast64_t;
    typedef __UINT_FAST64_TYPE__ uint_fast64_t;
    #define INT_FAST64_MAX __UINT_FAST64_MAX__
    #define INT_FAST64_MIN __UINT_FAST64_MIN__
    #define UINT_FAST64_MAX __UINT_FAST64_MAX__
#endif

#endif  /* INCLUDE_METALC_STDINT_H_ */
