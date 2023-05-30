/**
 * File autogenerated by CMake @CMAKE_VERSION@
 * Generating compiler: @CMAKE_C_COMPILER_ID@ @CMAKE_C_COMPILER_VERSION@
 *
 * DO NOT MODIFY.
 *
 * @file metalc.h
 */

#ifndef INCLUDE_METALC_METALC_H_
#define INCLUDE_METALC_METALC_H_

#include "internal/annotations.h"
#include "bits/architecture.h"

#cmakedefine01 METALC_COMPILER_GCC
#cmakedefine01 METALC_COMPILER_MINGW
#cmakedefine01 METALC_HAVE_EFI_H
#cmakedefine01 METALC_HAVE_FLOAT_H
#cmakedefine01 METALC_HAVE_LIMITS_H
#cmakedefine01 METALC_HAVE_STDARG_H
#cmakedefine01 METALC_HAVE_STDBOOL_H
#cmakedefine01 METALC_HAVE_STDDEF_H
#cmakedefine01 METALC_HAVE_STDINT_H
#cmakedefine01 METALC_COMPILE_OPTION_ENABLE_ALL_IO
#cmakedefine01 METALC_COMPILE_OPTION_USE_EFI
#cmakedefine01 METALC_COMPILE_OPTION_X86_USE_SHADOW_STACK
#cmakedefine01 METALC_COMPILE_OPTION_ENABLE_LONGLONG
#cmakedefine01 METALC_DISABLE_ASM_IMPLEMENTATIONS
#cmakedefine01 METALC_ABI_MICROSOFT
#cmakedefine01 METALC_ABI_GNU
#cmakedefine01 METALC_INTERNALS_USE_FASTCALL
#cmakedefine01 METALC_PLATFORM_UEFI_FULL
#cmakedefine01 METALC_PLATFORM_UEFI_RUNTIME_ONLY

/**
 * Was this implementation of the C standard library built without UEFI support?
 */
#define METALC_PLATFORM_NEED_UEFI (METALC_PLATFORM_UEFI_FULL || METALC_PLATFORM_UEFI_RUNTIME_ONLY)

#if METALC_COMPILE_OPTION_USE_EFI && (!METALC_HAVE_EFI_H)
    #error "Library was built needing UEFI support but doesn't appear to have `efi.h`."
#endif


/**
 * @def METALC_HAVE_LONG_LONG
 *
 * Does the target platform support the `long long` integer type?
 */
#if METALC_HAVE_LIMITS_H
    #include <limits.h>
    #ifdef LLONG_MAX
        #define METALC_HAVE_LONG_LONG   1
    #else
        #define METALC_HAVE_LONG_LONG   0
    #endif
#else
    #define METALC_HAVE_LONG_LONG   0
#endif


/**
 * @def METALC_HAVE_LONG_DOUBLE
 *
 * Does the target platform support the `long double` floating-point type?
 */
#if METALC_HAVE_FLOAT_H
    #include <float.h>
    #ifdef LDBL_MAX
        #define METALC_HAVE_LONG_DOUBLE 1
    #else
        #define METALC_HAVE_LONG_DOUBLE 0
    #endif
#else
    #define METALC_HAVE_LONG_DOUBLE 0
#endif


/**
 * Is this compiler compatible with GCC?
 */
#define METALC_COMPILER_GCC_COMPATIBLE      (METALC_COMPILER_GCC || METALC_COMPILER_MINGW)


/**
 * @def METALC_COMPILER_MS_COMPATIBLE
 *
 * Is this compiler compatible with the Windows family of compilers?
 *
 * This is mostly used to determine the calling convention the code written in
 * assembly language is supposed to use. It also determines how @ref stdint.h
 * works, since Windows doesn't provide it.
 */
#if defined _MSC_VER
    #define METALC_COMPILER_MS_COMPATIBLE 1
#else
    #define METALC_COMPILER_MS_COMPATIBLE 0
#endif


#define METALC_ENABLE_ASM_IMPLEMENTATIONS                               \
    (                                                                   \
      (!METALC_COMPILE_OPTION_DISABLE_ASM) &&                           \
      (METALC_COMPILER_GCC_COMPATIBLE || METALC_COMPILER_MS_COMPATIBLE) \
    )

#define METALC_EXPORT                        METALC_ATTR__EXPORT
#define METALC_EXPORT_WITH_ATTR(...)         METALC_ATTR__EXPORT GCC_ATTRIBUTE(__VA_ARGS__)

#if METALC_ENABLE_ASM_IMPLEMENTATIONS
    #define METALC_EXPORT_ASM                   METALC_EXPORT_WITH_ATTR(naked)
    #define METALC_EXPORT_ASM_WITH_ATTR(...)    METALC_EXPORT_WITH_ATTR(naked, __VA_ARGS__)
#else
    #define METALC_EXPORT_ASM                   METALC_EXPORT
    #define METALC_EXPORT_ASM_WITH_ATTR(...)    METALC_EXPORT_ASM GCC_ATTRIBUTE(__VA_ARGS__)
#endif


#if METALC_COMPILE_OPTION_ENABLE_ALL_IO
    #define METALC_COMPILE_OPTION_ENABLE_DISK_IO   1
    #define METALC_COMPILE_OPTION_ENABLE_TERM_IO   1
    #define METALC_COMPILE_OPTION_ENABLE_FILE_IO   1
#endif


#if !METALC_COMPILE_OPTION_ENABLE_DISK_IO
    #define METALC_COMPILE_OPTION_ENABLE_FILE_IO   0
#endif


#if METALC_COMPILE_OPTION_ENABLE_FILE_IO
    #define METALC_COMPILE_OPTION_ENABLE_DISK_IO   1
#endif


#if METALC_COMPILE_OPTION_USE_EFI
    #define METALC_COMPILE_OPTION_ENABLE_FILE_IO   1
    #define METALC_COMPILE_OPTION_ENABLE_DISK_IO   1
    #ifndef METALC_COMPILE_OPTION_HAVE_TERMINAL
        #define METALC_COMPILE_OPTION_HAVE_TERMINAL    1
    #endif
#endif


#if !METALC_COMPILE_OPTION_ENABLE_FILE_IO
    #define METALC_ATTRMARK_REQUIRES_FILEIO  METALC_EXPORT_WITH_ATTR(error ("Library not compiled with file I/O support."))
#else
    #define METALC_ATTRMARK_REQUIRES_FILEIO
#endif

#if !METALC_COMPILE_OPTION_HAVE_TERMINAL
    #define METALC_ATTRMARK_REQUIRES_TERM  METALC_EXPORT_WITH_ATTR(error ("Library not compiled with terminal I/O support."))
#else
    #define METALC_ATTRMARK_REQUIRES_TERM
#endif


#if METALC_COMPILE_FOR_TESTING
    /* Building the C library for testing... */

    /* No functions are internal to the C library anymore since we need to be
     * able to test these directly. Make the `METALC_INTERNAL_ONLY` markers a
     * no-op. */
    #define METALC_INTERNAL_ONLY                  METALC_ATTR__EXPORT
    #define METALC_INTERNAL_ONLY_WITH_ATTR(...)   METALC_ATTR__EXPORT GCC_ATTRIBUTE(__VA_ARGS__)

    #if METALC_BUILDING_LIBC
        /* We're building the C library but with the intent to run unit tests on
         * it. Since our testbench requires use of the host OS's standard C
         * library, we need to create aliases for all these exported functions
         * to avoid naming collisions. */
        #if defined METALC_BUILD_KIND_STATIC
            #define cstdlib_export(name)   \
                extern __typeof__(name) name METALC_ATTR__NO_EXPORT

            #define cstdlib_export_with_attr(name, ...)   \
                extern __typeof__(name) name METALC_ATTR__NO_EXPORT GCC_ATTRIBUTE(__VA_ARGS__)

            #define cstdlib_implement(name)     extern __typeof__(name) mclib_##name GCC_ATTRIBUTE(alias(#name), copy(name))
        #elif defined METALC_BUILD_KIND_SHARED
            #define cstdlib_export(name)   \
                METALC_ATTR__NO_EXPORT extern __typeof__(name) name

            #define cstdlib_export_with_attr(name, ...)   \
                METALC_ATTR__NO_EXPORT extern __typeof__(name) name GCC_ATTRIBUTE(__VA_ARGS__)

            #define cstdlib_implement(name)  extern __typeof__(name) mclib_##name GCC_ATTRIBUTE(alias(#name), copy(name))
        #else
            #error "Need to define METALC_BUILD_KIND_STATIC or METALC_BUILD_KIND_SHARED when compiling the C library in testing mode."
        #endif
    #else
        /* We're building the testbench code. */
        #define cstdlib_export(name)                    extern __typeof__(name) mclib_##name GCC_ATTRIBUTE((copy(name)))
        #define cstdlib_export_with_attr(name, ...)     extern __typeof__(name) mclib_##name GCC_ATTRIBUTE((copy(name), __VA_ARGS__))
        #define cstdlib_implement(name)
    #endif
#else
    /* Not in testing mode. We're either building the C library or a client
     * program is using the library. */
    #if METALC_INTERNALS_USE_FASTCALL && (METALC_TARGET_ARCHITECTURE_BITS != 64)
        #define METALC_INTERNAL_ONLY                  METALC_ATTR__NO_EXPORT METALC_ATTR__FASTCALL
    #else
        #define METALC_INTERNAL_ONLY                  METALC_ATTR__NO_EXPORT
    #endif

    #define METALC_INTERNAL_ONLY_WITH_ATTR(...)       METALC_INTERNAL_ONLY GCC_ATTRIBUTE(__VA_ARGS__)
    #define cstdlib_export(name)
    #define cstdlib_export_with_attr(name, ...)
    #define cstdlib_implement(name)
#endif  /* METALC_COMPILE_FOR_TESTING */

#endif  /* INCLUDE_METALC_METALC_H_ */
