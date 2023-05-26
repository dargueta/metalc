/**
 * Declarations for hook functions the kernel needs to implement.
 *
 * @file kernel_hooks.h
 */

#ifndef INCLUDE_METALC_KERNEL_HOOKS_H_
#define INCLUDE_METALC_KERNEL_HOOKS_H_

#include "metalc.h"
#include "stddef.h"
#include "bits/stdio.h"


/**
 * A hook function that suspends the calling process.
 *
 * Used to implement the default behavior of signals @ref SIGSTOP, @ref SIGTSTP,
 * @ref SIGTTIN, and @ref SIGTTOU. If this hook is not implemented, any of the
 * above signals will trigger @ref SIGSYS instead and terminate the process.
 */
METALC_API_EXPORT_WITH_ATTR(weak)
void krnlhook_suspend(int sig);


/**
 * A hook function that resumes the calling process.
 *
 * Used to implement the default behavior of @ref SIGCONT. If this hook is not
 * implemented, the process cannot be resumed, and @ref SIGSYS will be raised
 * instead.
 */
METALC_API_EXPORT_WITH_ATTR(weak)
void krnlhook_resume(int sig);


/**
 * A hook function to tell the OS to dump the core and terminate this process.
 *
 * If not implemented, any uncaught signal that would normally trigger a core
 * dump will behave like @ref SIGHUP. The original signal number is still
 * preserved in the runtime data structure passed back to the kernel.
 */
METALC_API_EXPORT_WITH_ATTR(noreturn, weak)
void krnlhook_core_dump(int sig);


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
 *
 * @return The page-aligned address to the allocated memory block. On error,
 *         returns @ref MAP_FAILED and @ref errno is set to indicate the cause.
 */
METALC_API_EXPORT_WITH_ATTR(weak)
void *krnlhook_mmap(
    void *addr, size_t length, int prot, int flags, int fd, mclib_off_t offset
);


/**
 * A hook function that implements at least part of the POSIX `mremap()` function.
 *
 * @param old_address
 * @param old_size
 * @param new_size
 * @param flags
 * @param new_address
 * @return
 */
METALC_API_EXPORT_WITH_ATTR(weak, nonnull(1))
void *krnlhook_mremap(
    void *old_address, size_t old_size, size_t new_size, int flags, ... /* void *new_address */
);


/**
 * Provided for symmetry with @ref krnlhook_mmap but might never be used.
 *
 * For the time being, kernels need not implement this. The default stub will
 * always succeed, regardless of its arguments.
 */
METALC_API_EXPORT_WITH_ATTR(weak, nonnull(1))
int krnlhook_munmap(void *addr, size_t length);


METALC_API_EXPORT_WITH_ATTR(weak, nonnull(1))
int krnlhook_open(const char *file, int mode, int perms);

METALC_API_EXPORT_WITH_ATTR(weak)
int krnlhook_close(int fdesc);

METALC_API_EXPORT_WITH_ATTR(weak, nonnull(2))
ssize_t krnlhook_write(int fdesc, const void *data, size_t size);

METALC_API_EXPORT_WITH_ATTR(weak, nonnull(2))
ssize_t krnlhook_read(int fdesc, void *buffer, size_t size);

METALC_API_EXPORT_WITH_ATTR(weak)
mclib_off_t krnlhook_seek(int fdesc, mclib_off_t offset, int whence);

METALC_API_EXPORT_WITH_ATTR(weak)
mclib_off_t krnlhook_tell(int fdesc);

METALC_API_EXPORT_WITH_ATTR(weak)
int krnlhook_fsync(int fdesc);


#endif  /* INCLUDE_METALC_KERNEL_HOOKS_H_ */
