#include <stdio.h>

#include <metalc/crtinit.h>
#include <metalc/errno.h>
#include <metalc/stdio.h>

#include "testing.h"


extern const struct UnitTestEntry kStringUnitTests[];

const struct UnitTestEntry *kAllUnitTestGroups[] = {
    kStringUnitTests,
    NULL
};


FILE *test_output_fd;

#define FAKE_PAGE_SIZE  4096
#define PAGE_MASK       (FAKE_PAGE_SIZE - 1)
#define DATA_AREA_SIZE  (32 * 1024 * 1024)


struct FakeOSState {
    void *heap_start;
    unsigned n_heap_pages;

    char data_area[DATA_AREA_SIZE];
    void *current_brk;
};


int krnlhook_brk(void *new_brk, void *udata) {
    struct FakeOSState *state = (struct FakeOSState *)udata;

    /* Ensure the new data break pointer is within allowable bounds. */
    if (
        ((char *)new_brk < state->data_area)
        || ((char *)new_brk >= (state->data_area + DATA_AREA_SIZE))
    ) {
        __mcapi_errno = __mcapi_EINVAL;
        return -1;
    }

    /* Address must be aligned on a page boundary */
    if ((uintptr_t)new_brk % FAKE_PAGE_SIZE != 0) {
        __mcapi_errno = __mcapi_EFAULT;
        return -1;
    }

    state->current_brk = new_brk;
    return 0;
}


int main(int argc, char **argv) {
    unsigned n_failed, n_succeeded, n_errored;
    size_t i;
    int result;
    const struct UnitTestEntry **group;
    const struct UnitTestEntry *current_test;
    MetalCRuntimeInfo rti;
    struct FakeOSState os_state;

    if (argc == 1)
        test_output_fd = stdout;
    else
        test_output_fd = fopen(argv[1], "w");

    /* Equivalent to memset(&rti, 0, sizeof(rti)) without using memset(). */
    for (i = 0; i < sizeof(rti); ++i)
        ((char *)&rti)[i] = 0;

    n_failed = n_succeeded = n_errored = 0;
    os_state.current_brk = os_state.data_area;

    for (group = kAllUnitTestGroups; group != NULL; ++group) {
        for (current_test = group[0]; current_test->name != NULL; ++current_test) {
            rti.main = current_test->function;
            rti.page_size = FAKE_PAGE_SIZE;
            rti.udata = &os_state;
            rti.original_brk = os_state.data_area;

            result = cstdlib_start(&rti, 0, NULL, NULL);
            fflush(test_output_fd);

            if (result == 0) {
                if (rti.signal_code != 0)
                    ++n_errored;
                if (rti.main_return_value == 0)
                    ++n_succeeded;
                else
                    ++n_failed;
            }
            else
                ++n_errored;
        }
    }

    if (test_output_fd != stdout)
        fclose(test_output_fd);

    return 0;
}
