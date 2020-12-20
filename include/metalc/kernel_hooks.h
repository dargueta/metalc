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
 * A hook function that implements at least part of the POSIX `mmap()` function.
 *
 * Required by @ref malloc. If this isn't implemented and @ref malloc is ever
 * called, the @ref SIGSYS signal will be raised and the process will be killed.
 *
 *
 * The kernel *does not* need to provide a full implementation of `mmap` for this
 * hook. When called by MetalC, the following guarantees apply:
 *
 * - If not NULL, @a addr is only a suggestion and need not be obeyed. It's
 *   guaranteed to be page-aligned. The hook MUST NOT fail if the address is
 *   unavailable but sufficient memory is present elsewhere.
 * - @a prot will always be the bitwise OR of @ref PROT_READ and @ref PROT_WRITE.
 * - @a length will always be a non-zero integer multiple of the page size given
 *   in the runtime info passed to @ref cstdlib_init.
 * - @a flags will always be the bitwise OR of the @ref MAP_PRIVATE and
 *   @ref MAP_ANONYMOUS flags.
 * - @a fd will always be -1.
 * - @a offset will always be 0.
 *
 * For full details on mmap's behavior, see the man pages for it, also available
 * at <https://www.man7.org/linux/man-pages/man2/mmap.2.html>.
 *
 * @param addr  If NULL, the kernel can pick any page-aligned address it wants.
 *              If not NULL, this is the starting address for the new mapping.
 * @param length    The number of bytes to allocate.
 * @param prot      Describes the desired memory protection of the mapping.
 * @param flags     Flags controlling how the memory should be allocated.
 * @param fd        (Ignored, always -1)
 * @param offset    (Ignored, always 0)
 * @param udata     The value of `udata` the C runtime was initialized with.
 *
 * @return The page-aligned address to the allocated memory block. On error,
 *         returns @ref MAP_FAILED and @ref errno is set to indicate the cause.
 */
void *krnlhook_mmap(
    void *addr, size_t length, int prot, int flags, int fd, __mcapi_off_t offset,
    void *udata
) __attribute__((weak));


/**
 * Provided for symmetry with @ref krnlhook_mmap but may never be used.
 *
 * For the time being, kernels need not implement this. The default stub will
 * always succeed, regardless of its arguments.
 */
int krnlhook_munmap(void *addr, size_t length, void *udata) __attribute__((weak, nonnull(1)));


int krnlhook_open(const char *file, int mode, int perms, void *udata) __attribute__((weak, nonnull(1)));
int krnlhook_close(int fdesc, void *udata) __attribute__((weak));
ssize_t krnlhook_write(int fdesc, const void *data, size_t size, void *udata) __attribute__((weak, nonnull(2)));
ssize_t krnlhook_read(int fdesc, void *buffer, size_t size, void *udata) __attribute__((weak, nonnull(2)));
__mcapi_off_t krnlhook_seek(int fdesc, __mcapi_off_t offset, int whence, void *udata) __attribute__((weak));
__mcapi_off_t krnlhook_tell(int fdesc, void *udata) __attribute__((weak));
int krnlhook_fsync(int fdesc, void *udata) __attribute__((weak));


#endif  /* INCLUDE_METALC_KERNEL_HOOKS_H_ */
