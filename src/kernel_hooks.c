#include "metalc/errno.h"
#include "metalc/metalc.h"
#include "metalc/setjmp.h"
#include "metalc/signal.h"
#include "metalc/stddef.h"
#include "metalc/stdint.h"
#include "metalc/stdio.h"

#include "metalc/sys/mman.h"
#include "metalc/bits/sys/mman.h"


extern jmp_buf __mcint_abort_target;


void krnlhook_suspend(int sig, void *udata) {
    (void)sig, (void)udata;
    raise(SIGSYS);
}

void krnlhook_resume(int sig, void *udata) {
    (void)sig, (void)udata;
    raise(SIGSYS);
}


void krnlhook_core_dump(int sig, void *udata) {
    (void)udata;
    longjmp(__mcint_abort_target, sig);
}


void *krnlhook_mmap(
    void *addr, size_t length, int prot, int flags, int fd, off_t offset,
    void *udata
) {
    (void)addr, (void)length, (void)prot, (void)flags, (void)fd, (void)offset,
    (void)udata;
    errno = ENOMEM;
    return MAP_FAILED;
}

int krnlhook_munmap(void *addr, size_t length, void *udata) {
    (void)addr, (void)length, (void)udata;
    /* Succeed unconditionally. This probably won't ever be called anyway. */
    errno = 0;
    return 0;
}


int krnlhook_open(const char *file, int mode, int perms, void *udata) {
    (void)file, (void)mode, (void)perms, (void)udata;
    errno = ENOSYS;
    return -1;
}


int krnlhook_close(int fdesc, void *udata) {
    (void)fdesc, (void)udata;
    errno = ENOSYS;
    return -1;
}


ssize_t krnlhook_write(int fdesc, const void *data, size_t size, void *udata) {
    (void)fdesc, (void)data, (void)size, (void)udata;
    errno = ENOSYS;
    return -1;
}


ssize_t krnlhook_read(int fdesc, void *buffer, size_t size, void *udata) {
    (void)fdesc, (void)buffer, (void)size, (void)udata;
    errno = ENOSYS;
    return -1;
}


off_t krnlhook_seek(int fdesc, off_t offset, int whence, void *udata) {
    (void)fdesc, (void)offset, (void)whence, (void)udata;
    errno = ENOSYS;
    return 0;
}


off_t krnlhook_tell(int fdesc, void *udata) {
    (void)fdesc, (void)udata;
    errno = ENOSYS;
    return -1;
}


int krnlhook_fsync(int fdesc, void *udata) {
    (void)fdesc, (void)udata;
    errno = ENOSYS;
    return -1;
}
