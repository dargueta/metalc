#include <metalc/errno.h>
#include <metalc/metalc.h>
#include <metalc/setjmp.h>
#include <metalc/signal.h>
#include <metalc/stddef.h>
#include <metalc/stdint.h>
#include <metalc/stdio.h>


extern __mcapi_jmp_buf __mcint_abort_target;


void krnlhook_suspend(int sig, void *udata) {
    (void)sig, (void)udata;
    raise(__mcapi_SIGSYS);
}

void krnlhook_resume(int sig, void *udata) {
    (void)sig, (void)udata;
    raise(__mcapi_SIGSYS);
}


void krnlhook_core_dump(int sig, void *udata) {
    (void)udata;
    longjmp(__mcint_abort_target, sig);
}


void *krnlhook_brk(void *new_brk, void *udata) {
    (void)new_brk, (void)udata;
    raise(__mcapi_SIGSYS);

    /* We should never get here unless there's a bug in our implementation of raise().*/
    __mcapi_errno = __mcapi_ENOSYS;
    return (void *)-1;
}


int krnlhook_open(const char *file, int mode, int perms, void *udata) {
    (void)file, (void)mode, (void)perms, (void)udata;
    __mcapi_errno = __mcapi_ENOSYS;
    return -1;
}


int krnlhook_close(intptr_t fdesc, void *udata) {
    (void)fdesc, (void)udata;
    __mcapi_errno = __mcapi_ENOSYS;
    return -1;
}


ssize_t krnlhook_write(intptr_t fdesc, const void *data, size_t size, void *udata) {
    (void)fdesc, (void)data, (void)size, (void)udata;
    __mcapi_errno = __mcapi_ENOSYS;
    return -1;
}


ssize_t krnlhook_read(intptr_t fdesc, void *buffer, size_t size, void *udata) {
    (void)fdesc, (void)buffer, (void)size, (void)udata;
    __mcapi_errno = __mcapi_ENOSYS;
    return -1;
}


__mcapi_off_t krnlhook_seek(
    intptr_t fdesc, __mcapi_off_t offset, int whence, void *udata
) {
    (void)fdesc, (void)offset, (void)whence, (void)udata;
    __mcapi_errno = __mcapi_ENOSYS;
    return 0;
}


__mcapi_off_t krnlhook_tell(intptr_t fdesc, void *udata) {
    (void)fdesc, (void)udata;
    __mcapi_errno = __mcapi_ENOSYS;
    return -1;
}


int krnlhook_fsync(intptr_t fdesc, void *udata) {
    (void)fdesc, (void)udata;
    __mcapi_errno = __mcapi_ENOSYS;
    return -1;
}
