/**
 * @file metalc.h
 */

#ifndef INCLUDE_METALC_METALC_H_
#define INCLUDE_METALC_METALC_H_

#include "internal/annotations.h"
#include "internal/architecture.h"
#include "internal/config.h"

/**
 * Was this implementation of the C standard library built without UEFI support?
 */
#define METALC_PLATFORM_NEED_UEFI                                                        \
    (METALC_PLATFORM_UEFI_FULL || METALC_PLATFORM_UEFI_RUNTIME_ONLY)

#if METALC_COMPILE_OPTION_USE_EFI && (!METALC_HAVE_EFI_H)
#    error "Library was built needing UEFI support but doesn't appear to have `efi.h`."
#endif

#if METALC_COMPILE_OPTION_ENABLE_ALL_IO || METALC_COMPILE_OPTION_USE_EFI
#    define METALC_ENABLE_DISK_IO 1
#    define METALC_ENABLE_TERM_IO 1
#    define METALC_ENABLE_FILE_IO 1
#else
#    define METALC_ENABLE_DISK_IO METALC_COMPILE_OPTION_ENABLE_DISK_IO

#    if METALC_COMPILE_OPTION_HAVE_TERMINAL
#        define METALC_ENABLE_TERM_IO METALC_COMPILE_OPTION_ENABLE_TERM_IO
#    else
#        define METALC_ENABLE_TERM_IO 0
#    endif

#    if METALC_COMPILE_OPTION_ENABLE_DISK_IO
#        define METALC_ENABLE_FILE_IO METALC_COMPILE_OPTION_ENABLE_FILE_IO
#    else
#        define METALC_ENABLE_FILE_IO 0
#    endif
#endif

/**
 * @def METALC_HAVE_LONG_LONG
 *
 * Does the target platform support the `long long` integer type?
 */
#include <limits.h>
#ifdef LLONG_MAX
#    define METALC_HAVE_LONG_LONG 1
#else
#    define METALC_HAVE_LONG_LONG 0
#endif

/**
 * @def METALC_HAVE_LONG_DOUBLE
 *
 * Does the target platform support the `long double` floating-point type?
 */
#include <float.h>
#ifdef LDBL_MAX
#    define METALC_HAVE_LONG_DOUBLE 1
#else
#    define METALC_HAVE_LONG_DOUBLE 0
#endif

/**
 * Is this compiler compatible with GCC?
 */
#define METALC_COMPILER_GCC_COMPATIBLE (METALC_COMPILER_GCC || METALC_COMPILER_MINGW)

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
#    define METALC_COMPILER_MS_COMPATIBLE 1
#else
#    define METALC_COMPILER_MS_COMPATIBLE 0
#endif

#define METALC_ENABLE_ASM_IMPLEMENTATIONS                                                \
    ((!METALC_COMPILE_OPTION_DISABLE_ASM) &&                                             \
     (METALC_COMPILER_GCC_COMPATIBLE || METALC_COMPILER_MS_COMPATIBLE))

#define METALC_EXPORT METALC_ATTR__EXPORT

#if METALC_ENABLE_ASM_IMPLEMENTATIONS
#    define METALC_EXPORT_ASM METALC_EXPORT GCC_ATTRIBUTE(naked)
#else
#    define METALC_EXPORT_ASM METALC_EXPORT
#endif

#if !METALC_ENABLE_FILE_IO
#    define METALC_ATTRMARK_REQUIRES_FILEIO                                              \
        GCC_ATTRIBUTE(error("Library not compiled with file I/O support."))
#else
#    define METALC_ATTRMARK_REQUIRES_FILEIO
#endif

#if !METALC_ENABLE_TERM_IO
#    define METALC_ATTRMARK_REQUIRES_TERM                                                \
        GCC_ATTRIBUTE(error("Library not compiled with terminal I/O support."))
#else
#    define METALC_ATTRMARK_REQUIRES_TERM
#endif

#ifdef __has_attribute
#    if __has_attribute(copy)
#        define GCC_ATTR_COPY(x) GCC_ATTRIBUTE(copy(x))
#    else
#        define GCC_ATTR_COPY(x)
#    endif
#else
#    define GCC_ATTR_COPY(x)
#endif

#if defined(METALC_CURRENTLY_COMPILING_LIBRARY)
#    define LIBC_GUARD(id) mclib_##id

/* No functions are internal to the C library anymore since we need to be
 * able to test these directly. Make the `METALC_INTERNAL_ONLY` markers a
 * no-op. */
#    define METALC_INTERNAL_ONLY METALC_ATTR__EXPORT

#    if defined(METALC_COMPILE_FOR_TESTING)
/* We're building the C library but with the intent to run unit tests on
 * it. Since our testbench requires use of the host OS's standard C
 * library, we need to create aliases for all these exported functions
 * to avoid naming collisions. */
#        define cstdlib_export(name) METALC_ATTR__NO_EXPORT extern __typeof__(name) name
#        define cstdlib_implement(name)                                                  \
            extern __typeof__(name) mclib_##name GCC_ATTRIBUTE(alias(#name))             \
                GCC_ATTR_COPY(name)
#    else
/* We're building the testbench code. */
#        define cstdlib_export(name)                                                     \
            extern __typeof__(name) mclib_##name GCC_ATTR_COPY(name)
#        define cstdlib_implement(name)
#    endif
#else
/* Not in testing mode. We're either building the C library or a client
 * program is using the library. */
#    define LIBC_GUARD(id) id
#    if METALC_INTERNALS_USE_FASTCALL && (METALC_TARGET_ARCHITECTURE_BITS != 64)
#        define METALC_INTERNAL_ONLY METALC_ATTR__NO_EXPORT METALC_ATTR__FASTCALL
#    else
#        define METALC_INTERNAL_ONLY METALC_ATTR__NO_EXPORT
#    endif

#    define cstdlib_export(name)
#    define cstdlib_implement(name)
#endif /* METALC_COMPILE_FOR_TESTING */

#endif /* INCLUDE_METALC_METALC_H_ */
