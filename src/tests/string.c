#include <metalc/string.h>
#include "testing.h"


BEGIN_TEST(test_memchr__basic)
    static const char *str = "Th\nisIsAString";
    assert(memchr(str, '\n', 5) == str + 2);
END_TEST()


BEGIN_TEST(test_memchr__not_found)
    assert(memchr("", '\n', 5) == NULL);
END_TEST()


BEGIN_TEST(test_memcmp__zero_length)
    assert(memcmp("", "", 0) == 0);
END_TEST()


BEGIN_TEST(test_memcmp__no_character_zero_equal)
    assert(memcmp("", "", 1) == 0);
END_TEST()


BEGIN_TEST(test_memcmp__one_character_nonzero_equal)
    assert(memcmp("A", "A", 1) == 0);
END_TEST()


const struct UnitTestEntry kStringUnitTests[] = {
    {test_memchr__basic, "memchr: basic"},
    {test_memchr__not_found, "memchr: zero-length string, not found"},
    {test_memcmp__zero_length, "memcmp: zero-length strings, zero length given"},
    {test_memcmp__no_character_zero_equal, "memcmp: zero-length strings, nonzero length given"},
    {test_memcmp__one_character_nonzero_equal, "memcmp: one character string, non-zero length given"},
    {NULL, NULL}
};
