/**
 * Dummy declarations of datatypes for systems without EFI headers.
 *
 * Only library C files should include this; it must never be exposed to client
 * code using the library. For systems with EFI headers this includes `efi.h`
 * and `efilib.h`.
 *
 * When compiling this library without EFI support, this header defines a few
 * datatypes defined in the EFI headers so we don't end up with hella "undeclared
 * identifier" errors in code that uses @ref MetalCRuntimeInfo.
 *
 * @file efi_shim.h
 */

#ifndef INCLUDE_METALC_INTERNAL_EFI_SHIM_H_
#define INCLUDE_METALC_INTERNAL_EFI_SHIM_H_


#include "../metalc.h"


#if METALC_HAVE_EFI_H
    #include <efi.h>
#endif

#if METALC_HAVE_EFILIB_H
    #include <efilib.h>
#endif


/* The EFI headers don't exist so we must be compiling in bare metal mode. */
#if !METALC_HAVE_EFI_H
    typedef void *EFI_HANDLE;
    typedef struct {
        /**
         * A useless pointer; ISO C requires structs to have at least one member.
         */
        void *dummy;
    } EFI_SYSTEM_TABLE;
    typedef unsigned long EFI_STATUS;
#endif


#endif  /* INCLUDE_METALC_INTERNAL_EFI_SHIM_H_ */
