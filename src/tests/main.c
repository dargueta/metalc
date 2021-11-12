#include <stdio.h>
#include <string.h>

#include <metalc/crtinit.h>

#include "testing.h"


extern const struct UnitTestEntry kStringUnitTests[];
extern const struct UnitTestEntry kFileIOUnitTests[];
extern const struct UnitTestEntry kCtypeUnitTests[];
extern const struct UnitTestEntry kWcharUtf8UnitTests[];
extern const struct UnitTestEntry kPrintfUnitTests[];


const struct UnitTestEntry *kAllUnitTestGroups[] = {
    kStringUnitTests,
    kFileIOUnitTests,
    kCtypeUnitTests,
    kWcharUtf8UnitTests,
    kPrintfUnitTests,
    NULL
};


FILE *test_output_fd;


int main(int argc, char **argv) {
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

    for (i_group = 0; kAllUnitTestGroups[i_group] != NULL; ++i_group) {
        group = kAllUnitTestGroups[i_group];
        for (i_test = 0; group[i_test].name != NULL; ++i_test) {
            current_test = &group[i_test];

            fprintf(stderr, "Running test: %s\n", current_test->name);
            memset(&rti, 0, sizeof(rti));

            rti.main = current_test->function;
            rti.page_size = 4096;
            rti.udata = NULL;

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

    if (test_output_fd != stdout)
        fclose(test_output_fd);
    return 0;
}
