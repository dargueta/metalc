#include <metalc/errno.h>
#include <metalc/fcntl.h>
#include <metalc/stdio.h>

#include "testing.h"


struct ModeStringTestCase {
    const char *mode_string;
    int expected_flags;
    int errno_value;
};


struct ModeStringTestCase mode_string_to_flags_cases[] = {
    {"w", O_WRONLY | O_TRUNC | O_CREAT, 0},
    {"wb", O_WRONLY | O_TRUNC | O_CREAT | O_BINARY, 0},
    {"w+", O_RDWR | O_TRUNC | O_CREAT, 0},
    {"w+b", O_RDWR | O_CREAT | O_TRUNC | O_BINARY, 0},
    {"wb+", O_RDWR | O_CREAT | O_TRUNC | O_BINARY, 0},
    {"wx", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0},
    {"w+x", O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0},
    {"wx+", O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0},
    {"w+xb", O_RDWR | O_CREAT | O_EXCL | O_TRUNC | O_BINARY, 0},
    {"w+bx", O_RDWR | O_CREAT | O_EXCL | O_TRUNC | O_BINARY, 0},
    {"wbx+", O_RDWR | O_CREAT | O_EXCL | O_TRUNC | O_BINARY, 0},
    {"r", O_RDONLY, 0},
    {"r+", O_RDWR, 0},
    {"rb", O_RDONLY | O_BINARY, 0},
    {"rb+", O_RDWR | O_BINARY, 0},
    {"r+b", O_RDWR | O_BINARY, 0},
    {"a", O_WRONLY | O_CREAT | O_APPEND, 0},
    {"a+", O_RDWR | O_CREAT | O_APPEND, 0},
    {"ab", O_WRONLY | O_CREAT | O_APPEND | O_BINARY, 0},
    {"a+b", O_RDWR | O_CREAT | O_APPEND | O_BINARY, 0},
    {"ab+", O_RDWR | O_CREAT | O_APPEND | O_BINARY, 0},
    {"R", -1, mclib_EINVAL},
    {"", -1, mclib_EINVAL},
    {"r+x", -1, mclib_EINVAL},
    {"ax", -1, mclib_EINVAL},
    {"a+x", -1, mclib_EINVAL},
    {NULL, 0, 0}
};


BEGIN_TEST(test_mode_string_to_flags__all)
    struct ModeStringTestCase *testcase;

    for (testcase = mode_string_to_flags_cases; testcase->mode_string != NULL; ++testcase) {
        INFO_MSG(
            "Testing mode string `%s`, expecting output %d and errno %d.",
            testcase->mode_string,
            testcase->expected_flags,
            testcase->errno_value
        );

        mclib_errno = 0;
        CHECK_EQ(
            mcinternal_mode_string_to_flags(testcase->mode_string),
            testcase->expected_flags
        );
        CHECK_EQ(mclib_errno, testcase->errno_value);
    }
END_TEST()


const struct UnitTestEntry kFileIOUnitTests[] = {
    {test_mode_string_to_flags__all, "mode_string_to_flags: all"},
    {NULL, NULL}
};
