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


void report_all_test_names(void) {
    int i_group, i_test, test_id;

    test_id = 0;
    for (i_group = 0; kAllUnitTestGroups[i_group] != NULL; ++i_group) {
        group = kAllUnitTestGroups[i_group];
        for (i_test = 0; group[i_test].name != NULL; ++i_test, ++test_id) {
            current_test = &group[i_test];
            testhook_report_test_name(test_id, current_test->name);
        }
    }
}


void run_test(int test_id) {
    int i_group, i_test, current_id, n_succeeded;

    current_id = 0;
    for (i_group = 0; kAllUnitTestGroups[i_group] != NULL; ++i_group) {
        group = kAllUnitTestGroups[i_group];
        for (i_test = 0; group[i_test].name != NULL; ++i_test, ++current_id) {
            if (current_id != test_id)
                continue;

            current_test = &group[i_test];

            memset(&rti, 0, sizeof(rti));
            rti.main = current_test->function;
            rti.page_size = FAKE_PAGE_SIZE;
            rti.udata = os_state;

            cstdlib_init(&rti);
            result = cstdlib_run(0, NULL, NULL);
            testhook_report_result(test_id, result);
            return;
        }
    }

    /* If we get out here then there is no test with that ID. We should fail
     * with an error in theory, but for now we'll quietly exit. */
}



void entry_point(int test_id) {
    if (test_id == -1)
        report_all_test_names();
    else
        run_test(test_id);
}
