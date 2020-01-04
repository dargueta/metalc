#ifndef INCLUDE_METALC_CRTINIT_H_
#define INCLUDE_METALC_CRTINIT_H_

#include <metalc/metalc.h>
#include <metalc/stdbool.h>
#include <metalc/stdint.h>


typedef void *(* cmetal_page_alloc_fn)(unsigned n_pages, void *udata);
typedef void *(* cmetal_page_free_fn)(void *base, unsigned count, void *udata);
typedef void (* cmetal_suspend_fn)(int sig, void *udata) /* __attribute__((cold)) */;
typedef void (* cmetal_resume_fn)(int sig, void *udata) /* __attribute__((cold)) */;
typedef void (* cmetal_core_dump_fn)(int sig, void *udata) __attribute__((noreturn));
typedef int (* cmetal_main_fn)(int argc, char **argv, char **env);
typedef int (* cmetal_brk_fn)(void *new_brk, void *udata);

typedef int (* cmetal_open_fn)(const char *file, int mode, int perms);
typedef ssize_t (* cmetal_write_fn)(intptr_t fdesc, const void *data, size_t size);
typedef ssize_t (* cmetal_read_fn)(intptr_t fdesc, void *buffer, size_t size);
typedef off_t (* cmetal_seek_fn)(intptr_t fdesc, off_t offset, int whence);
typedef off_t (* cmetal_tell_fn)(intptr_t fdesc);
typedef int (* cmetal_fsync_fn)(intptr_t fdesc);
typedef void (* cmetal_close_fn)(intptr_t fdesc);


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
     * Indicates if a core dump is necessary.
     *
     * TODO (dargueta): This is completely the wrong way to go about it.
     */
    bool need_core_dump;

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
     * any of the above signals will trigger @ref SIGTERM instead and terminate
     * the process.
     */
    cmetal_suspend_fn stop_process;

    /**
     * A callback function provided by the OS that resumes the calling process.
     *
     * Used to implement the default behavior of @ref SIGCONT. If this function
     * is `NULL`, the process cannot be resumed.
     */
    cmetal_resume_fn resume_process;

    /**
     * Pointer to a function implementing the POSIX `brk()` function.
     *
     * Required by @ref malloc.
     */
    cmetal_brk_fn f_brk;

    void *current_brk;

    cmetal_core_dump_fn f_core_dump;

    cmetal_open_fn f_io_open;
    cmetal_write_fn f_io_write;
    cmetal_read_fn f_io_read;
    cmetal_seek_fn f_io_lseek;
    cmetal_tell_fn f_io_tell;
    cmetal_fsync_fn f_io_fsync;
    cmetal_close_fn f_io_close;
} MetalCRuntimeInfo;


METALC_API_EXPORT int metalc_internal__start(
    MetalCRuntimeInfo *rti, int argc, char **argv, char **env
);

#endif  /* INCLUDE_METALC_CRTINIT_H_ */
