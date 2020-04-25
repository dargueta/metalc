#include <metalc/crtinit.h>
#include <metalc/errno.h>
#include <metalc/metalc.h>
#include <metalc/kernel_hooks.h>
#include <metalc/posix.h>

extern MetalCRuntimeInfo *__mcint_runtime_info;

static void *_current_brk = NULL;


int __mcint_brk(void *new_brk) {
    void *set_brk = krnlhook_brk(new_brk, __mcint_runtime_info->udata);

    if (set_brk == NULL) {
        __mcapi_errno = __mcapi_ENOMEM;
        return -1;
    }

    _current_brk = set_brk;
    return 0;
}


void *__mcint_sbrk(intptr_t diff) {
    void *old_brk, *new_brk;

    if (_current_brk == NULL) {
        /* Current data segment break is uninitialized; try setting it. */
        if (__mcint_brk(NULL) < 0) {
            __mcapi_errno = __mcapi_ENOMEM;
            return (void *)-1;
        }
    }

    /* If the caller passed in 0 they don't want to change the size. */
    if (diff == 0)
        return _current_brk;

    new_brk = (void *)((intptr_t)_current_brk + diff);
    old_brk = _current_brk;

    if (krnlhook_brk(new_brk, __mcint_runtime_info->udata) == NULL)
        return (void *)-1;

    _current_brk = new_brk;
    return old_brk;
}
