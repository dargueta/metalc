#include <stdio.h>
#include <string.h>

#include <metalc/crtinit.h>
#include <metalc/errno.h>
#include <metalc/kernel_hooks.h>
#include <metalc/sys/mman.h>

#include "testing.h"

extern const struct UnitTestEntry kStringUnitTests[];
extern const struct UnitTestEntry kFileIOUnitTests[];
extern const struct UnitTestEntry kCtypeUnitTests[];
extern const struct UnitTestEntry kWcharUtf8UnitTests[];
extern const struct UnitTestEntry kPrintfUnitTests[];

const struct UnitTestEntry *kAllUnitTestGroups[] = {kStringUnitTests, kFileIOUnitTests,
                                                    kCtypeUnitTests,  kWcharUtf8UnitTests,
                                                    kPrintfUnitTests, NULL};

FILE *test_output_fd;

#define PAGE_SIZE 4096
#define HEAP_SIZE (16 * PAGE_SIZE)

static char g_heap[HEAP_SIZE];

/** Pointer to the first invalid address. */
static char *g_heap_top = g_heap;

void *krnlhook_mmap(void *addr, size_t length, int prot, int flags, int fd,
                    mclib_off_t offset)
{
    void *old_top;

    /* For the purposes of testing we don't care about permissions nor flags. We
     * can't enforce them, anyway. */
    (void)prot, (void)flags, (void)fd, (void)offset;

    if (addr != NULL)
    {
        mclib_errno = mclib_ENOSYS;
        return mclib_MAP_FAILED;
    }

    /* Round up to the nearest page size */
    if (length % PAGE_SIZE != 0)
        length += PAGE_SIZE - (length % PAGE_SIZE);

    /* Can't do anything if we're at the top of the heap. */
    if ((g_heap_top + length) >= (g_heap + HEAP_SIZE))
    {
        mclib_errno = mclib_ENOMEM;
        return mclib_MAP_FAILED;
    }

    old_top = g_heap_top;
    g_heap_top += length;

    mclib_errno = 0;
    return old_top;
}

int main(int argc, char **argv)
{
    unsigned n_failed, n_succeeded, n_errored;
    int result, i_group, i_test;
    MetalCRuntimeInfo rti;
    const struct UnitTestEntry *group, *current_test;

    if (argc == 1)
        test_output_fd = stdout;
    else
        test_output_fd = fopen(argv[1], "w");

    n_failed = n_succeeded = n_errored = 0;
    initialize_test_log();

    for (i_group = 0; kAllUnitTestGroups[i_group] != NULL; ++i_group)
    {
        group = kAllUnitTestGroups[i_group];
        for (i_test = 0; group[i_test].name != NULL; ++i_test)
        {
            current_test = &group[i_test];

            fprintf(stderr, "Running test: %s\n", current_test->name);
            memset(&rti, 0, sizeof(rti));

            rti.main = current_test->function;
            rti.page_size = 4096;
            rti.udata = NULL;

            cstdlib_init(&rti);
            result = cstdlib_run(0, NULL, NULL);
            fflush(test_output_fd);

            if (result == 0)
            {
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

    if (test_output_fd != stdout)
        fclose(test_output_fd);
    return 0;
}
