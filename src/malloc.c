#include <metalc/assert.h>
#include <metalc/crtinit.h>
#include <metalc/errno.h>
#include <metalc/kernel_hooks.h>
#include <metalc/metalc.h>
#include <metalc/posix.h>
#include <metalc/signal.h>
#include <metalc/stdarg.h>
#include <metalc/stddef.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>
#include <metalc/string.h>


struct PointerEntry {
    void *base;
    uintptr_t size;
} __attribute__((aligned(4)));

extern MetalCRuntimeInfo *__mclib_runtime_info;

static void **g_heap_pages = NULL;
static struct PointerEntry *g_bookkeeping_pages = NULL;


#if METALC_ARCH_BITS == 16
    #define MINIMUM_ALLOCATION_SIZE     8
#elif METALC_ARCH_BITS == 32
    #define MINIMUM_ALLOCATION_SIZE     16
#else
    #define MINIMUM_ALLOCATION_SIZE     32
#endif


#define _extract_pointer(p, t)  ((t *)((uintptr_t)(p) & (~(uintptr_t)1)))
#define _is_allocated(p)        ((uintptr_t)(p) & (uintptr_t)1)


#define _malloc_assert(expression, message, ...) \
    __mcint_assert(expression, __LINE__, __FUNCTION__, __FILE__, "malloc(): " ## message, __VA_ARGS__)


static void *_allocate_pages(int count) {
    void *original_top = __mclib_sbrk(0);

    if (__mclib_sbrk(count * __mclib_runtime_info->page_size) != (void *)-1)
        return original_top;
    return NULL;
}


static struct PointerEntry *_page_containing_index(size_t index) {
    struct PointerEntry *current_page = g_bookkeeping_pages;

    while (current_page != NULL) {
        /* Page has no valid entries. This *must* be the last entry in the list.
         * if not, it was supposed to have been freed as soon as the last valid
         * entry was removed. */
        if (current_page[0].size == 0) {
            _malloc_assert(
                current_page[0].base == NULL,
                "Heap corruption detected -- Empty page should not point to a"
                " subsequent page. Offending page %p points to %p.",
                current_page, current_page[0].base
            );

            /* Hit the last page but the index wasn't found. This means the index
             * was past the end of the list. */
            return NULL;
        }

        if (index < (size_t)current_page[0].size)
            return current_page;

        /* If the index is beyond the end of this page's entries, skip to the
         * next page. */
        index -= current_page[0].size;
        current_page = (struct PointerEntry *)current_page[0].base;
    }

    /* Hit the end of the list. `index` was invalid. */
    return NULL;
}


static struct PointerEntry *_pointer_at_index(size_t index) {
    struct PointerEntry *page = _page_containing_index(index);

    if (page == NULL)
        return NULL;
    return &page[(index % (size_t)page->size) + 1];
}


static struct PointerEntry *_find_pointer(const void *pointer) {
    struct PointerEntry *entry;
    unsigned i;

    i = 0;
    do {
        entry = _pointer_at_index(i);

        /* Hit the end of the list without finding the pointer. */
        if (entry == NULL)
            return NULL;

        i += 1;

        /* If there's a bug and/or the heap got corrupted we could end up with a
         * cycle in our bookkeeping list. If that happens, we'd be stuck in an
         * infinite loop because `i` would overflow and we'd start searching at
         * the beginning again. Avoid that situation. */
        _malloc_assert(
            i != 0,
            "Heap corruption detected: Cycle found in the heap bookkeeping list."
        );
    } while(_extract_pointer(entry, const void) != pointer);

    return entry;
}


static uintptr_t _size_of_allocation(const void *pointer) {
    const struct PointerEntry *entry = _find_pointer(pointer);
    if (entry == NULL) {
        __mcapi_errno = __mcapi_EINVAL;
        return 0;
    }
    return entry->size;
}


METALC_API_INTERNAL int malloc_init(void) {
    __mclib_runtime_info->_original_brk = krnlhook_brk(NULL, __mclib_runtime_info->udata);

    if (__mclib_runtime_info->page_size == 0)
        return __mcapi_ENOSYS;

    g_heap_pages = _allocate_pages(1);
    if (g_heap_pages == NULL)
        return __mcapi_errno;

    g_bookkeeping_pages = _allocate_pages(1);
    if (g_bookkeeping_pages == NULL) {
        _allocate_pages(-1);
        return __mcapi_ENOMEM;
    }

    memset(g_heap_pages, 0, __mclib_runtime_info->page_size);

    g_heap_pages[1] = _allocate_pages(1);
    if (g_heap_pages[1] == NULL) {
        _allocate_pages(-2);
        return __mcapi_ENOMEM;
    }

    g_bookkeeping_pages[0].base = NULL;
    g_bookkeeping_pages[0].size = 1;
    g_bookkeeping_pages[1].base = g_heap_pages[1];
    g_bookkeeping_pages[1].size = __mclib_runtime_info->page_size;
    return 0;
}


METALC_API_INTERNAL int malloc_teardown(void) {
    krnlhook_brk(__mclib_runtime_info->_original_brk, __mclib_runtime_info->udata);
    return 0;
}


void *malloc(size_t size) {
    if (size == 0)
        return NULL;

    __mcapi_errno = __mcapi_ENOSYS;
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
        __mcapi_errno = __mcapi_ERANGE;
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
    struct PointerEntry *info;

    /* Ignore attempt to free a null pointer. */
    if (pointer == NULL)
        return;

    info = _find_pointer(pointer);
    _malloc_assert(info != NULL, "Attempted to free invalid pointer: %p", pointer);
    _malloc_assert(
        _is_allocated(info->base),
        "Attempted to free already free memory block at %p", pointer
    );

    /* Clear the low bit to indicate the block of memory is now free. */
    info->base = _extract_pointer(info->base, void);
}


#undef MINIMUM_ALLOCATION_SIZE
