#include <metalc/string.h>
#include "testing.h"


BEGIN_TEST(test_memchr__basic)
    static const char *str = "Th\nisIsAString";
    CHECK_EQ(memchr(str, '\n', 5), memchr(str, '\n', 5));
END_TEST()


BEGIN_TEST(test_memchr__zero_length)
    CHECK_EQ(memchr("", '\n', 5), NULL);
END_TEST()


BEGIN_TEST(test_memcmp__zero_length)
    CHECK_EQ(memcmp("", "", 0), 0);
END_TEST()


BEGIN_TEST(test_memcmp__one_character_zero_equal)
    CHECK_EQ(memcmp("", "", 1), 0);
END_TEST()


BEGIN_TEST(test_memcmp__one_character_nonzero_equal)
    CHECK_EQ(memcmp("A", "A", 1), 0);
END_TEST()


const struct UnitTestEntry kStringUnitTests[] = {
    {test_memchr__basic, "memchr: basic"},
    {test_memchr__zero_length, "memchr: zero-length string"},
    {test_memcmp__zero_length, "memcmp: zero-length string"},
    {test_memcmp__one_character_zero_equal, "memcmp: one character string, zero"},
    {test_memcmp__one_character_nonzero_equal, "memcmp: one character string, non-zero"}
};
