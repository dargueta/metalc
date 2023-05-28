/**
 * Inferences for the target machine's architecture.
 *
 * @file architecture.h
 */

#ifndef INCLUDE_METALC_BITS_ARCHITECTURE_H_
#define INCLUDE_METALC_BITS_ARCHITECTURE_H_

#define METALC_TARGET_ARCHITECTURE_X86_16   0
#define METALC_TARGET_ARCHITECTURE_X86_32   1
#define METALC_TARGET_ARCHITECTURE_X86_64   2
#define METALC_TARGET_ARCHITECTURE_MIPS32   3
#define METALC_TARGET_ARCHITECTURE_MIPS64   4
#define METALC_TARGET_ARCHITECTURE_ARM      5
#define METALC_TARGET_ARCHITECTURE_ARM64    6
#define METALC_TARGET_ARCHITECTURE_ITANIUM  7
#define METALC_TARGET_ARCHITECTURE_M68K     8
#define METALC_TARGET_ARCHITECTURE_POWERPC  9
#define METALC_TARGET_ARCHITECTURE_SPARC    10
#define METALC_TARGET_ARCHITECTURE_SPARC64  11

#define METALC_TARGET_ENDIANNESS_BIG    0
#define METALC_TARGET_ENDIANNESS_LITTLE 1


/* These macros are defined by various compilers to indicate the architecture
 * that the compiler is building for. This will work for:
 *
 * - GCC 4.1+ and compatible compilers like Clang and MinGW
 * - Visual Studio
 * - OpenWatcom
 * - Intel's C compiler (though possibly not IA-64)
 *
 * List obtained from: https://sourceforge.net/p/predef/wiki/Architectures/
 */
#if defined(_M_AMD64) || defined(__x86_64__) || defined(__x86_64) \
        || defined(__amd64__) || defined(__amd64)
#    if defined(__ILP32__) || defined(_ILP32)
         /* CPU is 64-bit but the target architecture is x32 */
#        define METALC_TARGET_ARCHITECTURE_BITS 32
#        define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_X86_32
#        define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_LITTLE
#    else
#        define METALC_TARGET_ARCHITECTURE_BITS 64
#        define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_X86_64
#        define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_LITTLE
#    endif
#elif defined(__386__) || defined(__386) || defined(__i386) \
        || defined(_M_I386) || defined(__pentium4__) \
        || defined(__i386__) || defined(__i486__) || defined(__i586__) \
        || defined(__i686__) || defined(__AS386_32__)
#    define METALC_TARGET_ARCHITECTURE_BITS 32
#    define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_X86_32
#    define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_LITTLE
#elif defined(__AS386_16__)
#    define METALC_TARGET_ARCHITECTURE_BITS 16
#    define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_X86_16
#    define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_LITTLE
#elif defined(_M_IX86)
#    if _M_IX86 < 300
         /* 16-bit x86*/
#        define METALC_TARGET_ARCHITECTURE_BITS 16
#        define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_X86_16
#        define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_LITTLE
#    elif _M_IX86 < 700
         /* 32-bit x86 */
#        define METALC_TARGET_ARCHITECTURE_BITS 32
#        define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_X86_32
#        define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_LITTLE
#    else
         /* P7 is the codename for Itanium so 700+ is *probably* Itanium, but we
          * can't make that assumption since it's not documented anywhere. */
#        error Unrecognized value for _M_IX86 target architecture macro.
#    endif
#elif defined(_M_ARM64) || defined(__aarch64__)
#    define METALC_TARGET_ARCHITECTURE_BITS 64
#    define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_ARM64
#    define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_BIG
#elif defined(_M_ARM)
#    if _M_ARM < 8
#        define METALC_TARGET_ARCHITECTURE_BITS 32
#        define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_ARM
#        define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_BIG
#    endif
#elif defined(__ia64__) || defined(__ia64) || defined(_M_IA64) || defined(__itanium__)
#    define METALC_TARGET_ARCHITECTURE_BITS 64
#    define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_ITANIUM
#    define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_LITTLE
#elif defined(__m68k__) || defined(__MC68K__)
#    define METALC_TARGET_ARCHITECTURE_BITS 32
#    define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_M68K
#    define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_BIG
#elif defined(__sparc_v8__) || defined(__sparcv8)
#    define METALC_TARGET_ARCHITECTURE_BITS 32
#    define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_SPARC
#    define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_BIG
#elif defined(__sparc_v9__) || defined(__sparcv9)
#    define METALC_TARGET_ARCHITECTURE_BITS 64
#    define METALC_TARGET_ARCHITECTURE_ID METALC_TARGET_ARCHITECTURE_SPARC64
#    define METALC_TARGET_ENDIANNESS_ID METALC_TARGET_ENDIANNESS_BIG
#endif

#ifndef METALC_TARGET_ARCHITECTURE_ID
#   error Cannot determine the target architecture.
#endif

#endif /* INCLUDE_METALC_BITS_ARCHITECTURE_H_ */
