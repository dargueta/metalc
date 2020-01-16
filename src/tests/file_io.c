#include <metalc/fcntl.h>
#include <metalc/stdio.h>

#include "testing.h"


BEGIN_TEST(test_mode_string_to_flags__w)
    CHECK_EQ(__mcint_mode_string_to_flags("w"), O_WRONLY | O_TRUNC);
END_TEST()


BEGIN_TEST(test_mode_string_to_flags__wplus)
    CHECK_EQ(__mcint_mode_string_to_flags("w+"), O_RDWR);
END_TEST()


const struct UnitTestEntry kFileIOUnitTests[] = {
    {test_mode_string_to_flags__w, "mode_string_to_flags: \"w\""},
    {NULL, NULL}
};
