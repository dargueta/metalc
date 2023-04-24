/**
 * Definitions of sized integers.
 *
 * @file stdint.h
 */

#ifndef INCLUDE_METALC_STDINT_H_
#define INCLUDE_METALC_STDINT_H_

#include <limits.h>     /* Provided by the compiler */

/* For convenience, we define the exact-size integer constants ahead of time
 * even though we don't know yet if we have types with these exact sizes. Later
 * in the file we'll undefine the constants for any type that doesn't have an
 * exact size on this platform. */

/* FIXME: we need to add the L suffixes where needed */
#ifdef __STDC__
#   define INT8_C(n)   (n)
#   define UINT8_C(n)  (n ## U)
#   define INT16_C(n)  (n)
#   define UINT16_C(n) (n ## U)
#   define INT32_C(n)  (n)
#   define UINT32_C(n) (n ## U)
#   define INT64_C(n)  (n)
#   define UINT64_C(n) (n ## U)
#else
    /* Nonstandard (probably K&R) C. Older compilers don't support the U suffix
     * so we leave that off here. */
#   define INT8_C(n)   (n)
#   define UINT8_C(n)  (n)
#   define INT16_C(n)  (n)
#   define UINT16_C(n) (n)
#   define INT32_C(n)  (n)
#   define UINT32_C(n) (n)
#   define INT64_C(n)  (n)
#   define UINT64_C(n) (n)
#endif

#define UINT8_MAX   UINT8_C(255)
#define INT8_MIN    INT8_C(-128)
#define INT8_MAX    INT8_C(127)
#define UINT16_MAX  UINT16_C(65535)
#define INT16_MIN   INT16_C(-32768)
#define INT16_MAX   INT16_C(32767)
#define UINT32_MAX  UINT32_C(4294967295)
#define INT32_MIN   INT32_C(-2147483648)
#define INT32_MAX   INT32_C(2147483647)
#define UINT64_MAX  UINT64_C(18446744073709551615)
#define INT64_MIN   INT64_C(-9223372036854775808)
#define INT64_MAX   INT64_C(9223372036854775807)

/******************************************************************************\
 *                            INT_LEAST##_T                                    *
\******************************************************************************/

/* `char` is the smallest unit and must be at least 8 bits. */
typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;

#define INT_LEAST8_MIN      SCHAR_MIN
#define INT_LEAST8_MAX      SCHAR_MAX
#define UINT_LEAST8_MAX     UCHAR_MAX

#if SCHAR_MAX >= INT16_MAX
    /* Unlikely, but theoretically a char could be >= 16 bits. */
    typedef signed char int_least16_t;
    typedef unsigned char uint_least16_t;

#   define INT_LEAST16_MIN  SCHAR_MIN
#   define INT_LEAST16_MAX  SCHAR_MAX
#   define UINT_LEAST16_MAX UCHAR_MAX
#else
    /* A short is defined by the standard to be at least 16 bits. */
    typedef signed short int_least16_t;
    typedef unsigned short uint_least16_t;

#   define INT_LEAST16_MIN  SHRT_MIN
#   define INT_LEAST16_MAX  SHRT_MAX
#   define UINT_LEAST16_MAX USHRT_MAX
#endif

#if SHRT_MAX >= INT32_MAX
    /* A short is at least 32 bits here. This is rare but it does happen in some
     * specialized systems. */
    typedef signed short int_least32_t;
    typedef unsigned short uint_least32_t;

#   define INT_LEAST32_MIN  SHRT_MIN
#   define INT_LEAST32_MAX  SHRT_MAX
#   define UINT_LEAST32_MAX USHRT_MAX
#elif INT_MAX >= INT32_MAX
    /* Int is at least 32 bits */
    typedef signed int int_least32_t;
    typedef unsigned int uint_least32_t;

#   define INT_LEAST32_MIN  INT_MIN
#   define INT_LEAST32_MAX  INT_MAX
#   define UINT_LEAST32_MAX UINT_MAX
#elif defined(LONG_MAX)
    /* Int is the same size as a short (probably 16 bits), which means we must
     * use a long for 32 bits. */
    typedef signed long int_least32_t;
    typedef unsigned long uint_least32_t;

#   define INT_LEAST32_MIN  LONG_MIN
#   define INT_LEAST32_MAX  LONG_MAX
#   define UINT_LEAST32_MAX ULONG_MAX
#else
    /* If we get here then this compiler doesn't have the `long` type, and we
     * don't have a reliable way of defining a 32-bit integer.
     *
     * This only happens in compilers implementing a pre-K&R subset of the
     * language. Those will certainly blow up with other language features this
     * library relies on (such as structs), BUT we do want to be able to work
     * with someone who's writing their own C compiler and doesn't want to build
     * the entire standard library themselves. */
#   undef INT32_C
#   undef UINT32_C
#   warning This compiler does not support 32-bit integers.
#endif

#if SHRT_MAX >= INT64_MAX
    /* According to Wikipedia some systems actually do have 64-bit shorts. This
     * is known as the SILP64 data model. */
    typedef signed short int_least64_t;
    typedef unsigned short uint_least64_t;

#   define INT_LEAST64_MIN  SHRT_MIN
#   define INT_LEAST64_MAX  SHRT_MAX
#   define UINT_LEAST64_MAX USHRT_MAX
#elif INT_MAX >= INT64_MAX
    /* An int is at least 64 bits. Rare, but again, it does happen. */
    typedef signed int int_least64_t;
    typedef unsigned int uint_least64_t;

#   define INT_LEAST64_MIN  INT_MIN
#   define INT_LEAST64_MAX  INT_MAX
#   define UINT_LEAST64_MAX UINT_MAX
#elif defined(LONG_MAX) && (LONG_MAX >= INT64_MAX)
    /* `long` is at least 64 bits. */
    typedef signed long int_least64_t;
    typedef unsigned long uint_least64_t;

#   define INT_LEAST64_MIN  LONG_MIN
#   define INT_LEAST64_MAX  LONG_MAX
#   define UINT_LEAST64_MAX ULONG_MAX
#elif defined(LLONG_MAX)
    /* Compiler defines a `long long` which by definition must be at least
     * 64 bits. */
    typedef signed long long int_least64_t;
    typedef unsigned long long uint_least64_t;

#   define INT_LEAST64_MIN  LLONG_MIN
#   define INT_LEAST64_MAX  LLONG_MAX
#   define UINT_LEAST64_MAX ULLONG_MAX
#else
    /* No way to define a 64-bit integer. */
#   undef INT64_C
#   undef UINT64_C
#   warning This compiler does not support 64-bit integers.
#endif

/******************************************************************************\
 *                          EXACT INTEGER SIZES                                *
\******************************************************************************/

/* To reduce code duplication we'll define these ahead of time and undefine them
 * as needed if we don't have the exact integer size. */
#define HAVE_EXACT_INT8
#define HAVE_EXACT_INT16
#define HAVE_EXACT_INT32
#define HAVE_EXACT_INT64

#if defined(__INT8_TYPE__)
    typedef __INT8_TYPE__ int8_t;
    typedef __UINT8_TYPE__ uint8_t;
#elif defined(_MSC_VER)
    typedef signed __int8 int8_t;
    typedef unsigned __int8 uint8_t;
#elif defined(__WATCOMC__)
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
#elif UINT_LEAST8_MAX == UINT8_MAX
    typedef int_least8_t int8_t;
    typedef uint_least8_t uint8_t;
#else
    /* No integer with exactly 8 bits */
#   undef INT8_MIN
#   undef INT8_MAX
#   undef UINT8_MAX
#   undef HAVE_EXACT_INT8
#endif

#if defined(__INT16_TYPE__)
    typedef __INT16_TYPE__ int16_t;
    typedef __UINT16_TYPE__  uint16_t;
#elif defined(_MSC_VER) && defined(_INTEGRAL_MAX_BITS) && (_INTEGRAL_MAX_BITS >= 16)
    typedef signed __int16 int16_t;
    typedef unsigned __int16 uint16_t;
#elif defined(__WATCOMC__)
    typedef signed short int16_t;
    typedef unsigned short uint16_t;
#elif INT_LEAST16_MAX == INT16_MAX
    typedef int_least16_t int16_t;
    typedef uint_least16_t uint16_t;
#else
    /* No integer with exactly 16 bits */
#   undef INT16_MIN
#   undef INT16_MAX
#   undef UINT16_MAX
#   undef HAVE_EXACT_INT16
#endif

#if defined(__INT32_TYPE__)
    typedef __INT32_TYPE__ int32_t;
    typedef __UINT32_TYPE__  uint32_t;
#elif defined(_MSC_VER) && defined(_INTEGRAL_MAX_BITS) && (_INTEGRAL_MAX_BITS >= 32)
    typedef signed __int32 int32_t;
    typedef unsigned __int32 uint32_t;
#elif defined(__WATCOMC__)
    typedef signed long int32_t;
    typedef unsigned long uint32_t;
#elif defined(INT_LEAST32_MAX) && (INT_LEAST32_MAX == INT32_MAX)
    typedef int_least32_t int32_t;
    typedef uint_least32_t uint32_t;
#else
    /* No integer with exactly 32 bits */
#   undef INT32_MIN
#   undef INT32_MAX
#   undef UINT32_MAX
#   undef HAVE_EXACT_INT32
#endif

#if defined(__INT64_TYPE__)
    typedef __INT64_TYPE__ int64_t;
    typedef __UINT64_TYPE__  uint64_t;
#elif defined(_MSC_VER) && defined(_INTEGRAL_MAX_BITS) && (_INTEGRAL_MAX_BITS >= 64)
    /* Microsoft */
    typedef signed __int64 int64_t;
    typedef unsigned __int64 uint64_t;
#elif defined(__WATCOMC__) && defined(LLONG_MAX)
    typedef signed long long int64_t;
    typedef unsigned long long uint64_t;
#elif defined(INT_LEAST64_MAX) && (INT_LEAST64_MAX == INT64_MAX)
    typedef int_least64_t int64_t;
    typedef uint_least64_t uint64_t;
#else
    /* No integer with exactly 64 bits */
#   undef INT64_MIN
#   undef INT64_MAX
#   undef UINT64_MAX
#   undef HAVE_EXACT_INT64
#endif

/******************************************************************************\
 *                          GUESSING POINTER SIZE                              *
\******************************************************************************/

/* These macros are defined by various compilers to indicate the architecture
 * that the compiler is building for. This will work for:
 *
 * - GCC 4.1+ and compatible compilers like Clang and MinGW
 * - Visual Studio
 * - OpenWatcom
 * - Intel's C compiler (though possibly not IA-64)
 */
#if defined(__LP64__) ||    \
    defined(_M_AMD64) ||    \
    defined(_M_ARM64) ||    \
    defined(__AVX__)  ||    \
    defined(__AVX2__) ||    \
    defined(_M_X64)   ||    \
    defined(__x86_64__) ||  \
    defined(__x86_64) ||    \
    defined(__w64)    ||    \
    (defined(_M_IX86) && (_M_IX86 >= 600)) ||    \
    (defined(__MINGW64__) && !defined(__MINGW32__)) || \
    (defined(__SIZEOF_POINTER__) && (__SIZEOF_POINTER__ == 8))
#   define POINTER_IS_64BIT
#elif defined(__386__) ||                                           \
    defined(__pentium4__) ||                                        \
    defined(__AS386_32__) ||                                        \
    (defined(_M_IX86) && (_M_IX86 < 600) && (_M_IX86 >= 300)) ||    \
    (defined(__MINGW32__) && !defined(__MINGW64__)) ||              \
    (defined(__SIZEOF_POINTER__) && (__SIZEOF_POINTER__ == 4))
#   define POINTER_IS_32BIT
#elif (defined(_M_IX86) && (_M_IX86 < 300)) || defined(__AS386_16__)
#   define POINTER_IS_16BIT
#else
#   error Cannot determine the architecture size.
#endif

/******************************************************************************\
*                              INTPTR_T                                       *
\******************************************************************************/

#if defined(__INTPTR_TYPE__)
    typedef __INTPTR_TYPE__ intptr_t;
    typedef __UINTPTR_TYPE__ uintptr_t;
#   define INTPTR_MIN __INTPTR_MIN__
#   define INTPTR_MAX __INTPTR_MAX__
#   define UINTPTR_MAX __UINTPTR_MAX__
#elif defined(POINTER_IS_64BIT)
    typedef int_least64_t intptr_t;
    typedef uint_least64_t uintptr_t;
#   define INTPTR_MIN INT_LEAST64_MIN
#   define INTPTR_MAX INT_LEAST64_MAX
#   define UINTPTR_MAX UINT_LEAST64_MAX
#elif defined(POINTER_IS_32BIT)
    typedef int_least32_t intptr_t;
    typedef uint_least32_t uintptr_t;
#   define INTPTR_MIN INT_LEAST32_MIN
#   define INTPTR_MAX INT_LEAST32_MAX
#   define UINTPTR_MAX UINT_LEAST32_MAX
#elif defined(POINTER_IS_16BIT)
    typedef int_least16_t intptr_t;
    typedef uint_least16_t uintptr_t;
#   define INTPTR_MIN INT_LEAST16_MIN
#   define INTPTR_MAX INT_LEAST16_MAX
#   define UINTPTR_MAX UINT_LEAST16_MAX
#else
#   error BUG: Architecture detected successfully but identifier not set. Please file a bug ticket.
#endif

/******************************************************************************\
*                             PTRDIFF_T                                       *
\******************************************************************************/

#ifdef __PTRDIFF_TYPE__
    typedef __PTRDIFF_TYPE__ ptrdiff_t;
#elif defined(POINTER_IS_64BIT)
    typedef int_least64_t ptrdiff_t;
#elif defined(POINTER_IS_32BIT)
    typedef int_least32_t ptrdiff_t;
#elif defined(POINTER_IS_16BIT)
    typedef int_least16_t ptrdiff_t;
#else
#   error Unable to determine the target architecture pointer size.
#endif

/******************************************************************************\
*                              INTMAX_T                                       *
\******************************************************************************/

#if defined(__INTMAX_TYPE__)
    typedef __INTMAX_TYPE__ intmax_t;
    typedef __UINTMAX_TYPE__ uintmax_t;
#   define INTMAX_MIN __INTMAX_MIN__
#   define INTMAX_MAX __INTMAX_MAX__
#   define UINTMAX_MAX __UINTMAX_MAX__
#elif (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64) || defined(INT_LEAST64_MAX)
    /* This won't be accurate for systems that support integers greater than 64
     * bits, but it's good enough... right?
     * (_INTEGRAL_MAX_BITS is defined on Visual Studio compilers and the Intel C
     * compiler when built for Windows.) */
    typedef int_least64_t intmax_t;
    typedef uint_least64_t uintmax_t;

#   define INTMAX_MIN  INT_LEAST64_MIN
#   define INTMAX_MAX  INT_LEAST64_MAX
#   define UINTMAX_MAX UINT_LEAST64_MAX
#elif (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 32) || defined(INT_LEAST32_MAX)
    typedef int_least32_t intmax_t;
    typedef uint_least32_t uintmax_t;

#   define INTMAX_MIN  INT_LEAST32_MIN
#   define INTMAX_MAX  INT_LEAST32_MAX
#   define UINTMAX_MAX UINT_LEAST32_MAX
#else
    /* If we get here then either:
     *
     * - We're on Visual Studio and _INTEGRAL_MAX_BITS is less than 32, or
     * - We're on a different compiler and we don't have int_least32_t.
     *
     * If this is the case then we're probably compiling for a 16-bit system.
     * We can't assume it's exactly 16 bits, as there are some 18- and 24-bit
     * architectures (such as the PDP-11) that a retro computing enthusiast may
     * want to build for. */
    typedef int_least16_t intmax_t;
    typedef uint_least16_t uintmax_t;

#   define INTMAX_MIN  INT_LEAST16_MIN
#   define INTMAX_MAX  INT_LEAST16_MAX
#   define UINTMAX_MAX UINT_LEAST16_MAX
#endif

/******************************************************************************\
*                             INT_FAST##_T                                    *
\******************************************************************************/

/* GCC and some compatible compilers define macros that expand to the C types
 * with the attributes we need. Since we have no idea of the underlying hardware,
 * we need to rely on these to be able to define the int_fast*_t types. */

#if defined(__INT_FAST8_TYPE__)
    typedef __INT_FAST8_TYPE__ int_fast8_t;
    typedef __UINT_FAST8_TYPE__ uint_fast8_t;
#   define INT_FAST8_MAX __UINT_FAST8_MAX__
#   define INT_FAST8_MIN __UINT_FAST8_MIN__
#   define UINT_FAST8_MAX __UINT_FAST8_MAX__
#endif

#if defined(__INT_FAST16_TYPE__)
    typedef __INT_FAST16_TYPE__ int_fast16_t;
    typedef __UINT_FAST16_TYPE__ uint_fast16_t;
#   define INT_FAST16_MAX __UINT_FAST16_MAX__
#   define INT_FAST16_MIN __UINT_FAST16_MIN__
#   define UINT_FAST16_MAX __UINT_FAST16_MAX__
#endif

#if defined(__INT_FAST32_TYPE__)
    typedef __INT_FAST32_TYPE__ int_fast32_t;
    typedef __UINT_FAST32_TYPE__ uint_fast32_t;
#   define INT_FAST32_MAX __UINT_FAST32_MAX__
#   define INT_FAST32_MIN __UINT_FAST32_MIN__
#   define UINT_FAST32_MAX __UINT_FAST32_MAX__
#endif

#if defined(__INT_FAST64_TYPE__)
    typedef __INT_FAST64_TYPE__ int_fast64_t;
    typedef __UINT_FAST64_TYPE__ uint_fast64_t;
#   define INT_FAST64_MAX __UINT_FAST64_MAX__
#   define INT_FAST64_MIN __UINT_FAST64_MIN__
#   define UINT_FAST64_MAX __UINT_FAST64_MAX__
#endif

/******************************************************************************\
*                              CLEANUP                                        *
\******************************************************************************/

#ifdef POINTER_IS_64BIT
#   undef POINTER_IS_64BIT
#endif
#ifdef POINTER_IS_32BIT
#   undef POINTER_IS_64BIT
#endif
#ifdef POINTER_IS_16BIT
#   undef POINTER_IS_16BIT
#endif

#endif  /* INCLUDE_METALC_STDINT_H_ */
