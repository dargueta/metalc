#include <metalc/crtinit.h>
#include <metalc/errno.h>
#include <metalc/metalc.h>
#include <metalc/posix.h>

extern MetalCRuntimeInfo *__mclib_runtime_info;

void *__mclib_current_brk __attribute__((visibility("hidden"))) = NULL;


void *sbrk(intptr_t diff) {
    void *old_brk, *new_brk;

    if (__mclib_runtime_info->f_brk == NULL) {
        errno = ENOSYS;
        return (void *)-1;
    }

    if (__mclib_current_brk == NULL) {
        /* Current data segment break is uninitialized; try setting it. Fail if
         * the OS didn't tell us where it is; presumably f_brk isn't implemented
         * either. */
        if (__mclib_runtime_info->original_brk == NULL) {
            errno = ENOSYS;
            return (void *)-1;
        }

        __mclib_current_brk = __mclib_runtime_info->original_brk;
    }

    /* If the caller passed in 0 they don't want to change the size. */
    if (diff == 0)
        return __mclib_current_brk;

    new_brk = (void *)((intptr_t)__mclib_current_brk + diff);
    old_brk = __mclib_current_brk;

    if (__mclib_runtime_info->f_brk(new_brk, __mclib_runtime_info->udata) < 0)
        return (void *)-1;

    __mclib_current_brk = new_brk;
    return old_brk;
}
