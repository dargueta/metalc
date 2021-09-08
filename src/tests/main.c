#include <metalc/crtinit.h>

#include "testing.h"


extern const struct UnitTestEntry kStringUnitTests[];
extern const struct UnitTestEntry kFileIOUnitTests[];
extern const struct UnitTestEntry kCtypeUnitTests[];

static MetalCRuntimeInfo g_rti;


static const struct UnitTestEntry * const kAllUnitTestGroups[] = {
    kStringUnitTests,
    kFileIOUnitTests,
    kCtypeUnitTests,
    NULL
};


int main(int argc, char **argv) {
    (void)argc, (void)argv;

    int i_group, i_test, test_id;
    const struct UnitTestEntry *group;

    test_id = 0;
    for (i_group = 0; kAllUnitTestGroups[i_group] != NULL; ++i_group) {
        group = kAllUnitTestGroups[i_group];
        for (i_test = 0; group[i_test].name != NULL; ++i_test, ++test_id) {
            g_rti.udata = (void *)((intptr_t)test_id);
            g_rti.page_size = 4096;
            g_rti.main = group[i_test].function;
            g_rti.stdin_handle = 0;
            g_rti.stdout_handle = 0;
            g_rti.stderr_handle = 0;

            cstdlib_init(&g_rti);
            cstdlib_run(0, NULL, NULL);
        }
    }

    return 0;
}
