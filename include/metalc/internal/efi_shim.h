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
#include "../stdint.h"

#if METALC_HAVE_EFI_H
#    include <efi.h>
#elif METALC_HAVE_EFILIB_H
#    include <efilib.h>
#else
/* The EFI headers don't exist so we must be compiling in bare metal mode. */

/** Dummy definition of the real EFI ``EFI_HANDLE`` type. */
typedef intptr_t EFI_HANDLE;

/**
 * Dummy definition of the real EFI ``EFI_SYSTEM_TABLE`` type.
 *
 * In the real EFI headers this is defined as a struct, but if we're not using
 * EFI support then it doesn't really matter what this is, does it?
 */
typedef intptr_t EFI_SYSTEM_TABLE;

/**
 * Dummy definition of the EFI ``EFI_STATUS`` type used for return values.
 *
 * This was taken from the real efi.h file on Ubuntu 20.04 so it's probably
 * accurate. Not that it matters.
 */
typedef unsigned long EFI_STATUS;
#endif

#endif /* INCLUDE_METALC_INTERNAL_EFI_SHIM_H_ */
