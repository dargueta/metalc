#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <metalc/crtinit.h>
#include <metalc/errno.h>

#include "testing.h"


extern const struct UnitTestEntry kStringUnitTests[];
extern const struct UnitTestEntry kFileIOUnitTests[];
extern const struct UnitTestEntry kCtypeUnitTests[];


const struct UnitTestEntry *kAllUnitTestGroups[] = {
    kStringUnitTests,
    kFileIOUnitTests,
    kCtypeUnitTests,
    NULL
};


FILE *test_output_fd;

#define FAKE_PAGE_SIZE  4096
#define PAGE_MASK       (FAKE_PAGE_SIZE - 1)
#define DATA_AREA_SIZE  (32 * 1024 * 1024)


struct FakeOSState {
    void *current_brk;
    char data_area[DATA_AREA_SIZE];
};


void *krnlhook_brk(void *new_brk, void *udata) {
    struct FakeOSState *state = (struct FakeOSState *)udata;

    if (new_brk == NULL) {
        /* printf("# DEBUG: Requested current break: %p\n", state->current_brk); */
        return state->current_brk;
    }

    /* Ensure the new data break pointer is within allowable bounds. */
    if (
        ((char *)new_brk < state->data_area)
        || ((char *)new_brk >= (state->data_area + DATA_AREA_SIZE))
    ) {
        fprintf(
            stderr,
            "\nERROR: new_brk out of bounds: %p not in [%p, %p)\n\n",
            new_brk, state->data_area, state->data_area + DATA_AREA_SIZE
        );
        __mcapi_errno = __mcapi_EINVAL;
        return NULL;
    }

    state->current_brk = new_brk;
    /* printf("# DEBUG: Setting data break to %p\n", new_brk); */
    return new_brk;
}


int main(int argc, char **argv) {
    unsigned n_failed, n_succeeded, n_errored;
    int result, i_group, i_test;
    MetalCRuntimeInfo rti;
    const struct UnitTestEntry *group, *current_test;
    struct FakeOSState *os_state;

    if (argc == 1)
        test_output_fd = stdout;
    else
        test_output_fd = fopen(argv[1], "w");

    os_state = malloc(sizeof(*os_state));
    memset(os_state, 0, sizeof(*os_state));
    os_state->current_brk = os_state->data_area;

    n_failed = n_succeeded = n_errored = 0;
    initialize_test_log();

    for (i_group = 0; kAllUnitTestGroups[i_group] != NULL; ++i_group) {
        group = kAllUnitTestGroups[i_group];
        for (i_test = 0; group[i_test].name != NULL; ++i_test) {
            current_test = &group[i_test];

            fprintf(stderr, "Running test: %s\n", current_test->name);
            memset(&rti, 0, sizeof(rti));

            rti.main = current_test->function;
            rti.page_size = FAKE_PAGE_SIZE;
            rti.udata = os_state;

            cstdlib_init(&rti);
            result = cstdlib_run(0, NULL, NULL);
            fflush(test_output_fd);

            if (result == 0) {
                if (rti.signal_code != 0)
                    ++n_errored;
                else if (rti.main_return_value == 0)
                    ++n_succeeded;
                else
                    ++n_failed;
            }
            else
                ++n_errored;
        }
    }

    free(os_state);

    if (test_output_fd != stdout)
        fclose(test_output_fd);
    return 0;
}
