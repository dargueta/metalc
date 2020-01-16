#include <metalc/fcntl.h>
#include <metalc/stdio.h>

#include "testing.h"


BEGIN_TEST(test_mode_string_to_flags__w)
    CHECK_EQ(__mcint_mode_string_to_flags("w"), O_WRONLY | O_TRUNC | O_CREAT);
END_TEST()


BEGIN_TEST(test_mode_string_to_flags__wplus)
    CHECK_EQ(__mcint_mode_string_to_flags("w+"), O_RDWR | O_TRUNC | O_CREAT);
END_TEST()


BEGIN_TEST(test_mode_string_to_flags__wplusx)
    CHECK_EQ(__mcint_mode_string_to_flags("w+x"), O_RDWR | O_CREAT | O_EXCL);
END_TEST()


BEGIN_TEST(test_mode_string_to_flags__r)
    CHECK_EQ(__mcint_mode_string_to_flags("r"), O_RDONLY);
END_TEST()


BEGIN_TEST(test_mode_string_to_flags__rplus)
    CHECK_EQ(__mcint_mode_string_to_flags("r+"), O_RDWR);
END_TEST()


const struct UnitTestEntry kFileIOUnitTests[] = {
    {test_mode_string_to_flags__w, "mode_string_to_flags: \"w\""},
    {test_mode_string_to_flags__wplus, "mode_string_to_flags: \"w+\""},
    {test_mode_string_to_flags__wplusx, "mode_string_to_flags: \"w+x\""},
    {test_mode_string_to_flags__r, "mode_string_to_flags: \"r\""},
    {test_mode_string_to_flags__rplus, "mode_string_to_flags: \"r+\""},
    {NULL, NULL}
};
