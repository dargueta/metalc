#ifndef INCLUDE_METALC_CRTINIT_H_
#define INCLUDE_METALC_CRTINIT_H_

#include <metalc/metalc.h>
#include <metalc/stddef.h>
#include <metalc/stdint.h>
#include <metalc/stdio.h>


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
     *
     */
    cmetal_main_fn main;

    intptr_t stdin_handle;
    intptr_t stdout_handle;
    intptr_t stderr_handle;

    /**
     * A pointer to the first byte past the end of this process' writable data
     * segment.
     *
     * MetalC will not modify the value it receives here, and expects it not to
     * change after the library's initialized. It's used by @ref sbrk and
     * @ref malloc to allocate/free writable memory to use for the heap.
     */
    void *original_brk;
} MetalCRuntimeInfo;


METALC_API_EXPORT int cstdlib_start(
    MetalCRuntimeInfo *rti, int argc, char **argv, char **env
);

#endif  /* INCLUDE_METALC_CRTINIT_H_ */
