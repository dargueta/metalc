#include <metalc/ctype.h>
#include <metalc/stddef.h>

#include "testing.h"


BEGIN_TEST(isalnum__basic)
    CHECK_EQ(isalnum('A'), 1);
    CHECK_EQ(isalnum('F'), 1);
    CHECK_EQ(isalnum('Z'), 1);
    CHECK_EQ(isalnum('a'), 1);
    CHECK_EQ(isalnum('j'), 1);
    CHECK_EQ(isalnum('z'), 1);
    CHECK_EQ(isalnum('0'), 1);
    CHECK_EQ(isalnum('9'), 1);
END_TEST()


BEGIN_TEST(isalpha__basic)
END_TEST()


BEGIN_TEST(isblank__basic)
END_TEST()


BEGIN_TEST(iscntrl__basic)
END_TEST()


BEGIN_TEST(isdigit__basic)
END_TEST()


BEGIN_TEST(isgraph__basic)
END_TEST()


BEGIN_TEST(islower__basic)
END_TEST()


BEGIN_TEST(isprint__basic)
END_TEST()


BEGIN_TEST(ispunct__basic)
END_TEST()


BEGIN_TEST(isspace__basic)
END_TEST()


BEGIN_TEST(isupper__basic)
END_TEST()


BEGIN_TEST(isxdigit__basic)
END_TEST()


BEGIN_TEST(tolower__basic)
END_TEST()


BEGIN_TEST(toupper__basic)
END_TEST()


const struct UnitTestEntry kCtypeUnitTests[] = {
    {isalnum__basic, "isalnum: basic"},
    {isalpha__basic, "isalpha: basic"},
    {isblank__basic, "isblank: basic"},
    {iscntrl__basic, "iscntrl: basic"},
    {isdigit__basic, "isdigit: basic"},
    {isgraph__basic, "isgraph: basic"},
    {islower__basic, "islower: basic"},
    {isprint__basic, "isprint: basic"},
    {ispunct__basic, "ispunct: basic"},
    {isspace__basic, "isspace: basic"},
    {isupper__basic, "isupper: basic"},
    {isxdigit__basic, "isxdigit: basic"},
    {tolower__basic, "tolower: basic"},
    {toupper__basic, "toupper: basic"},
    {NULL, NULL}
};
