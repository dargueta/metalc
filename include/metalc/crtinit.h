#ifndef INCLUDE_METALC_CRTINIT_H_
#define INCLUDE_METALC_CRTINIT_H_

#include <metalc/metalc.h>
#include <metalc/stddef.h>
#include <metalc/stdint.h>
#include <metalc/stdio.h>


typedef void (* cmetal_suspend_fn)(int sig, void *udata);
typedef void (* cmetal_resume_fn)(int sig, void *udata);
typedef void (* cmetal_core_dump_fn)(int sig, void *udata) __attribute__((noreturn));
typedef int (* cmetal_main_fn)(int argc, char **argv, char **env);
typedef int (* cmetal_brk_fn)(void *new_brk, void *udata);

typedef int (* cmetal_open_fn)(const char *file, int mode, int perms, void *udata);
typedef __mcapi_ssize_t (* cmetal_write_fn)(intptr_t fdesc, const void *data, size_t size, void *udata);
typedef __mcapi_ssize_t (* cmetal_read_fn)(intptr_t fdesc, void *buffer, size_t size, void *udata);
typedef __mcapi_off_t (* cmetal_seek_fn)(intptr_t fdesc, __mcapi_off_t offset, int whence, void *udata);
typedef __mcapi_off_t (* cmetal_tell_fn)(intptr_t fdesc, void *udata);
typedef int (* cmetal_fsync_fn)(intptr_t fdesc, void *udata);
typedef void (* cmetal_close_fn)(intptr_t fdesc, void *udata);


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
     * A callback function provided by the OS that suspends the calling process.
     *
     * Used to implement the default behavior of signals @ref SIGSTOP,
     * @ref SIGTSTP, @ref SIGTTIN, and @ref SIGTTOU. If this function is `NULL`,
     * any of the above signals will trigger @ref SIGSYS instead and terminate
     * the process.
     */
    cmetal_suspend_fn stop_process;

    /**
     * A callback function provided by the OS that resumes the calling process.
     *
     * Used to implement the default behavior of @ref SIGCONT. If this function
     * is `NULL`, the process cannot be resumed, and @ref SIGSYS will be raised
     * instead.
     */
    cmetal_resume_fn resume_process;

    /**
     * Pointer to a function implementing the POSIX `brk()` function.
     *
     * Required by @ref malloc. If this isn't implemented and @ref malloc is
     * ever called, the @ref SIGSYS signal will be raised and the process will
     * be killed.
     */
    cmetal_brk_fn f_brk;

    /**
     * A pointer to the first byte past the end of this process' writable data
     * segment.
     *
     * MetalC will not modify the value it receives here, and expects it not to
     * change after the library's initialized. It's used by @ref sbrk and
     * @ref malloc to allocate/free writable memory to use for the heap.
     */
    void *original_brk;

    /**
     * A callback function to tell the OS to dump the core and terminate this
     * process.
     *
     * If not given, any uncaught signal that would normally trigger a core dump
     * will behave like @ref SIGHUP. The original signal number is still preserved.
     */
    cmetal_core_dump_fn f_core_dump;

    cmetal_open_fn f_io_open;
    cmetal_write_fn f_io_write;
    cmetal_read_fn f_io_read;
    cmetal_seek_fn f_io_lseek;
    cmetal_tell_fn f_io_tell;
    cmetal_fsync_fn f_io_fsync;
    cmetal_close_fn f_io_close;
} MetalCRuntimeInfo;


METALC_API_EXPORT int cstdlib_start(
    MetalCRuntimeInfo *rti, int argc, char **argv, char **env
);

#endif  /* INCLUDE_METALC_CRTINIT_H_ */
