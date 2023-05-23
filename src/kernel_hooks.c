#include "metalc/errno.h"
#include "metalc/metalc.h"
#include "metalc/setjmp.h"
#include "metalc/signal.h"
#include "metalc/stddef.h"
#include "metalc/stdint.h"
#include "metalc/stdio.h"

#include "metalc/sys/mman.h"


extern mclib_jmp_buf mcinternal_abort_target;


void krnlhook_suspend(int sig) {
    (void)sig;
    raise(mclib_SIGSYS);
}

void krnlhook_resume(int sig) {
    (void)sig;
    raise(mclib_SIGSYS);
}


void krnlhook_core_dump(int sig) {
    longjmp(mcinternal_abort_target, sig);
}


void *krnlhook_mmap(
    void *addr, size_t length, int prot, int flags, int fd, mclib_off_t offset
) {
    (void)addr, (void)length, (void)prot, (void)flags, (void)fd, (void)offset;
    mclib_errno = mclib_ENOMEM;
    return mclib_MAP_FAILED;
}


void *krnlhook_mremap(
    void *old_address, size_t old_size, size_t new_size, int flags, ... /* void *new_address */
) {
    (void)old_address, (void)old_size, (void)new_size, (void)flags;
    mclib_errno = mclib_ENOSYS;
    return mclib_MAP_FAILED;
}


int krnlhook_munmap(void *addr, size_t length) {
    (void)addr, (void)length;
    /* Succeed unconditionally. This probably won't ever be called anyway. */
    mclib_errno = 0;
    return 0;
}


int krnlhook_open(const char *file, int mode, int perms) {
    (void)file, (void)mode, (void)perms;
    mclib_errno = mclib_ENOSYS;
    return -1;
}


int krnlhook_close(int fdesc) {
    (void)fdesc;
    mclib_errno = mclib_ENOSYS;
    return -1;
}


ssize_t krnlhook_write(int fdesc, const void *data, size_t size) {
    (void)fdesc, (void)data, (void)size;
    mclib_errno = mclib_ENOSYS;
    return -1;
}


ssize_t krnlhook_read(int fdesc, void *buffer, size_t size) {
    (void)fdesc, (void)buffer, (void)size;
    mclib_errno = mclib_ENOSYS;
    return -1;
}


mclib_off_t krnlhook_seek(int fdesc, mclib_off_t offset, int whence) {
    (void)fdesc, (void)offset, (void)whence;
    mclib_errno = mclib_ENOSYS;
    return 0;
}


mclib_off_t krnlhook_tell(int fdesc) {
    (void)fdesc;
    mclib_errno = mclib_ENOSYS;
    return -1;
}


int krnlhook_fsync(int fdesc) {
    (void)fdesc;
    mclib_errno = mclib_ENOSYS;
    return -1;
}
