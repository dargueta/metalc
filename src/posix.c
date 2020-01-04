#include <metalc/crtinit.h>
#include <metalc/metalc.h>
#include <metalc/posix.h>

extern MetalCRuntimeInfo *gRuntimeInfo;


void *sbrk(intptr_t diff) {
    void *old_brk, *new_brk;

    if (gRuntimeInfo->current_brk == NULL) {
        /* Current break is uninitialized; try setting it. */
        if (gRuntimeInfo->f_brk(0, gRuntimeInfo->udata) < 0)
            return (void *)-1;
    }

    if (diff == 0)
        return gRuntimeInfo->current_brk;

    new_brk = (void *)((intptr_t)gRuntimeInfo->current_brk + diff);
    old_brk = gRuntimeInfo->current_brk;

    if (gRuntimeInfo->f_brk(new_brk, gRuntimeInfo->udata) < 0)
        return (void *)-1;
    return old_brk;
}
