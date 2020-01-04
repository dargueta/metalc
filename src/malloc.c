#include <metalc/assert.h>
#include <metalc/crtinit.h>
#include <metalc/errno.h>
#include <metalc/metalc.h>
#include <metalc/signal.h>
#include <metalc/stdarg.h>
#include <metalc/stddef.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>
#include <metalc/string.h>

#pragma pack(push, 2)
struct PointerEntry {
    void *base;
    uintptr_t size;
};
#pragma pack(pop)


extern MetalCRuntimeInfo *gRuntimeInfo;

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


METALC_API_INTERNAL void _malloc_assert(int expression, const char *message, ...) {
    FILE *out;
    va_list args;

    if (expression)
        return;

    out = (stderr != NULL) ? stderr : stdout;
    if (out) {
        va_start(args, message);
        vfprintf(out, "malloc() assertion failed: %s\n", args);
        va_end(args);
    }

    raise(SIGABRT);
}


METALC_API_INTERNAL void *_request_new_page(unsigned count) {
    (void)count;
    /*
    unsigned page_index, page_offset, i, pointers_per_page;

    void *new_pages = gRuntimeInfo->allocate_pages(count, gRuntimeInfo->udata);
    if (new_pages == NULL)
        return ENOMEM;

    pointers_per_page = gRuntimeInfo->page_size / sizeof(void *);
    for (i = 0; i < count; ++i) {
        ;
    }
*/
    errno = ENOSYS;
    return NULL;
}


METALC_API_INTERNAL struct PointerEntry *_page_containing_index(size_t index) {
    struct PointerEntry *current_page = g_bookkeeping_pages;

    while (current_page != NULL) {
        /* Page has no valid entries. This *must* be the last entry in the list.
         * if not, it was supposed to have been freed as soon as the last valid
         * entry was removed. */
        if (current_page[0].size == 0) {
            _malloc_assert(
                current_page[0].base == NULL,
                "Heap corruption detected: Empty page should not point to a"
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


METALC_API_INTERNAL struct PointerEntry *_pointer_at_index(size_t index) {
    struct PointerEntry *page = _page_containing_index(index);

    if (page == NULL)
        return NULL;
    return &page[(index % (size_t)page->size) + 1];
}


METALC_API_INTERNAL struct PointerEntry *_find_pointer(const void *pointer) {
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


METALC_API_INTERNAL uintptr_t _size_of_allocation(const void *pointer) {
    const struct PointerEntry *entry = _find_pointer(pointer);
    if (entry == NULL) {
        errno = EINVAL;
        return 0;
    }
    return entry->size;
}


METALC_API_INTERNAL int malloc_init(void) {
    g_heap_pages = gRuntimeInfo->allocate_pages(1, gRuntimeInfo->udata);
    if (g_heap_pages == NULL)
        return ENOMEM;

    g_bookkeeping_pages = gRuntimeInfo->allocate_pages(1, gRuntimeInfo->udata);
    if (g_bookkeeping_pages == NULL) {
        gRuntimeInfo->free_pages(g_heap_pages, 1, gRuntimeInfo->udata);
        return ENOMEM;
    }

    memset(g_heap_pages, 0, gRuntimeInfo->page_size);

    g_heap_pages[1] = gRuntimeInfo->allocate_pages(1, gRuntimeInfo->udata);
    if (g_heap_pages[1] == NULL) {
        gRuntimeInfo->free_pages(g_heap_pages, 1, gRuntimeInfo->udata);
        gRuntimeInfo->free_pages(g_bookkeeping_pages, 1, gRuntimeInfo->udata);
        return ENOMEM;
    }

    g_bookkeeping_pages[0].base = NULL;
    g_bookkeeping_pages[0].size = 1;
    g_bookkeeping_pages[1].base = g_heap_pages[1];
    g_bookkeeping_pages[1].size = gRuntimeInfo->page_size;
    return 0;
}


METALC_API_INTERNAL int malloc_teardown(void) {
    void **current_page_pointer, **tracker_page, **next_tracker_page;

    tracker_page = g_heap_pages;

    while (tracker_page != NULL) {
        current_page_pointer = &tracker_page[1];
        while (current_page_pointer != NULL) {
            gRuntimeInfo->free_pages(*current_page_pointer, 1, gRuntimeInfo->udata);
            ++current_page_pointer;
        }
        next_tracker_page = current_page_pointer[0];
        gRuntimeInfo->free_pages(tracker_page, 1, gRuntimeInfo->udata);
        tracker_page = next_tracker_page;
    }

    return 0;
}


METALC_API_EXPORT void *malloc(size_t size) {
    if (size == 0)
        return NULL;

    errno = ENOSYS;
    return NULL;
}


METALC_API_EXPORT void *calloc(size_t n_elements, size_t element_size) {
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


METALC_API_EXPORT void *realloc(void *pointer, size_t new_size) {
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


METALC_API_EXPORT void free(void *pointer) {
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
