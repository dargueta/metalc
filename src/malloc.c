#include "metalc/assert.h"
#include "metalc/crtinit.h"
#include "metalc/errno.h"
#include "metalc/kernel_hooks.h"
#include "metalc/metalc.h"
#include "metalc/signal.h"
#include "metalc/stdarg.h"
#include "metalc/stddef.h"
#include "metalc/stdio.h"
#include "metalc/stdlib.h"
#include "metalc/string.h"
#include "metalc/sys/mman.h"


extern MetalCRuntimeInfo *__mcint_runtime_info;


#if METALC_ARCH_BITS == 16
    #define MINIMUM_ALLOCATION_SIZE     8
    #define MINIMUM_MMAP_REQUEST_SIZE   1024    /* 1 KiB */
#elif METALC_ARCH_BITS == 32
    #define MINIMUM_ALLOCATION_SIZE     16
    #define MINIMUM_MMAP_REQUEST_SIZE   4194304     /* 4 MiB */
#else
    #define MINIMUM_ALLOCATION_SIZE     32
    #define MINIMUM_MMAP_REQUEST_SIZE   4194304     /* 4 MiB */
#endif


struct _MemoryBlock {
    void *p_previous;
    uintptr_t block_size;
};


static _MemoryBlock *g_ptr_first_page = NULL;


/* Yes, yes, this is terrible, but we're only using it for one thing. */
#define MAX(x, y)  ((x) < (y)) ? (y) : (x)


static void *allocate_pages(size_t n_pages, void *suggested_address) {
    return krnlhook_mmap(
        suggested_address,
        n_pages * __mcint_runtime_info->page_size,
        PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS,
        -1,
        0
    );
}


METALC_API_INTERNAL int malloc_init(void) {
    size_t request_size;

    /* The minimum allocation size depends on the architecture. For 16-bit builds,
     * it's 1 KiB. Otherwise, 4 MiB. */
    request_size = MAX(MINIMUM_MMAP_REQUEST_SIZE, __mcint_runtime_info->page_size);
    g_ptr_first_page = (struct _MemoryBlock *)krnlhook_mmap(
        NULL,
        request_size,
        PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS,
        -1,
        0
    );

    if (g_ptr_first_page == MAP_FAILED)
        /* If mmap failed, then errno is already set for us. */
        return errno;

    g_ptr_first_page->p_previous = NULL;
    g_ptr_first_page->block_size = request_size;

    return 0;
}


METALC_API_INTERNAL int malloc_teardown(void) {
    return 0;
}


void *malloc(size_t size) {
    if (size == 0)
        return NULL;

    errno = ENOSYS;
    return NULL;
}


void *calloc(size_t n_elements, size_t element_size) {
    size_t total_size;
    void *pointer;

    if ((n_elements == 0) || (element_size == 0))
        return NULL;

    total_size = n_elements * element_size;

    /* Bail out if n_elements * element_size overflows. */
    if (total_size / element_size != n_elements) {
        errno = ERANGE;
        return NULL;
    }

    pointer = malloc(total_size);
    if (pointer == NULL)
        return pointer;

    memset(pointer, 0, total_size);
    return pointer;
}


void *realloc(void *pointer, size_t new_size) {
    uintptr_t old_size;
    void *new_pointer;

    if (new_size == 0) {
        free(pointer);
        return NULL;
    }
    else if (pointer == NULL)
        return malloc(new_size);

    /* Inefficient implementation. The smart way to do it is to try and resize
     * the current block, and if the block can be resized, then update the
     * allocation map and return the same pointer.
     *
     * For the sake of simplicity, here we instead allocate a completely new block
     * of memory, copy the old contents, and free the original block. This can
     * falsely claim it's run out of memory because we're holding two copies of
     * the same block in memory at once. */
    old_size = _size_of_allocation(pointer);
    new_pointer = malloc(new_size);
    if (new_pointer == NULL)
        /* errno already set by malloc(), no need to do it here. */
        return NULL;

    memcpy(new_pointer, pointer, old_size);
    free(pointer);
    return new_pointer;
}


void free(void *pointer) {
}


#undef MINIMUM_ALLOCATION_SIZE
#undef MINIMUM_MMAP_REQUEST_SIZE
#undef MAX
