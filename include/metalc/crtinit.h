/**
 * Definitions of important types and data structures for the C library startup code.
 *
 * @file crtinit.h
 */

#ifndef INCLUDE_METALC_CRTINIT_H_
#define INCLUDE_METALC_CRTINIT_H_

#include "internal/efi_shim.h"
#include "metalc.h"
#include "stddef.h"
#include "stdint.h"


/**
 * A pointer to the (nonstandard) three-argument variant of the C `main()` function.
 *
 * Code taking
 */
typedef int (* cmetal_main_fn)(int argc, char **argv, char **env);


/**
 * Configuration information passed to the C library from the operating system.
 */
typedef struct {
    /**
     * User-defined argument passed to the C runtime initialization function.
     *
     * The C library doesn't modify or look at this; it's purely for the operating
     * system's use. All callbacks take a `udata` argument that this gets passed
     * in as.
     */
    void *udata;

    /**
     * The size of a single page, in bytes.
     *
     * This must be set by the operating system before initializing the C library.
     * Failing to do so can cause unpredictable behavior.
     */
    unsigned page_size;

    /**
     * The return value from main().
     *
     * Only valid after start() has returned. If the process terminated abnormally,
     * or initializing the C library failed, this will be -1. However, -1 is a
     * valid return value for main() so you'll need to check @ref signal_code as
     * well.
     */
    int main_return_value;

    /**
     * The signal that the process was terminated with, if applicable.
     *
     * Only valid after `start()` has returned. If the process terminated normally,
     * this will be 0.
     */
    int signal_code;

    /**
     * A pointer to the main() function the C library will execute.
     */
    cmetal_main_fn main;

    intptr_t stdin_handle;
    intptr_t stdout_handle;
    intptr_t stderr_handle;

    /**
     * The original data break address when the library was first initialized.
     *
     * @warning Internal use only. Do not modify.
     */
    void *_original_brk;


    /**
     * On UEFI-aware builds, the EFI image handle.
     *
     * Typedefed to a void pointer on bare metal builds.
     */
    EFI_HANDLE efi_image_handle;

    /**
     * On UEFI-aware builds, a pointer to the EFI system table.
     *
     * Typedefed to a void pointer on bare metal builds.
     */
    EFI_SYSTEM_TABLE *efi_system_table;
} MetalCRuntimeInfo;


METALC_API_EXPORT int cstdlib_start(
    MetalCRuntimeInfo *rti, int argc, char **argv, char **env
);

#endif  /* INCLUDE_METALC_CRTINIT_H_ */
