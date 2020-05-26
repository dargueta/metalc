#ifndef INCLUDE_METALC_KERNEL_HOOKS_H_
#define INCLUDE_METALC_KERNEL_HOOKS_H_

#include "metalc.h"
#include "stddef.h"
#include "stdint.h"
#include "stdio.h"


/**
 * A hook function that suspends the calling process.
 *
 * Used to implement the default behavior of signals @ref SIGSTOP, @ref SIGTSTP,
 * @ref SIGTTIN, and @ref SIGTTOU. If this hook is not implemented, any of the
 * above signals will trigger @ref SIGSYS instead and terminate the process.
 */
void krnlhook_suspend(int sig, void *udata) __attribute__((weak));


/**
 * A hook function that resumes the calling process.
 *
 * Used to implement the default behavior of @ref SIGCONT. If this hook is not
 * implemented, the process cannot be resumed, and @ref SIGSYS will be raised
 * instead.
 */
void krnlhook_resume(int sig, void *udata) __attribute__((weak));


/**
 * A hook function to tell the OS to dump the core and terminate this process.
 *
 * If not implemented, any uncaught signal that would normally trigger a core
 * dump will behave like @ref SIGHUP. The original signal number is still
 * preserved in the runtime data structure passed back to the kernel.
 */
void krnlhook_core_dump(int sig, void *udata) __attribute__((noreturn, weak));


/**
 * A hook function that implements the POSIX `brk()` function.
 *
 * Required by @ref malloc. If this isn't implemented and @ref malloc is ever
 * called, the @ref SIGSYS signal will be raised and the process will be killed.
 *
 * @param
 */
void *krnlhook_brk(void *new_brk, void *udata) __attribute__((weak));
int krnlhook_open(const char *file, int mode, int perms, void *udata) __attribute__((weak));
int krnlhook_close(intptr_t fdesc, void *udata) __attribute__((weak));
ssize_t krnlhook_write(intptr_t fdesc, const void *data, size_t size, void *udata) __attribute__((weak));
ssize_t krnlhook_read(intptr_t fdesc, void *buffer, size_t size, void *udata) __attribute__((weak));
__mcapi_off_t krnlhook_seek(intptr_t fdesc, __mcapi_off_t offset, int whence, void *udata) __attribute__((weak));
__mcapi_off_t krnlhook_tell(intptr_t fdesc, void *udata) __attribute__((weak));
int krnlhook_fsync(intptr_t fdesc, void *udata) __attribute__((weak));


#endif  /* INCLUDE_METALC_KERNEL_HOOKS_H_ */
