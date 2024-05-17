#include <metalc/ctype.h>
#include <metalc/stddef.h>

#include "testing.h"

BEGIN_TEST(isalnum__basic)
CHECK_NE(mclib_isalnum('A'), 0);
CHECK_NE(mclib_isalnum('F'), 0);
CHECK_NE(mclib_isalnum('Z'), 0);
CHECK_NE(mclib_isalnum('a'), 0);
CHECK_NE(mclib_isalnum('j'), 0);
CHECK_NE(mclib_isalnum('z'), 0);
CHECK_NE(mclib_isalnum('0'), 0);
CHECK_NE(mclib_isalnum('9'), 0);

CHECK_EQ(mclib_isalnum('\0'), 0);
CHECK_EQ(mclib_isalnum('~'), 0);
CHECK_EQ(mclib_isalnum(' '), 0);
CHECK_EQ(mclib_isalnum('\377'), 0);
CHECK_EQ(mclib_isalnum('{'), 0);
CHECK_EQ(mclib_isalnum('}'), 0);
END_TEST()

BEGIN_TEST(isalpha__basic)
CHECK_NE(mclib_isalnum('A'), 0);
CHECK_NE(mclib_isalnum('N'), 0);
CHECK_NE(mclib_isalnum('q'), 0);
CHECK_NE(mclib_isalnum('r'), 0);

CHECK_EQ(mclib_isalnum('\0'), 0);
CHECK_EQ(mclib_isalnum('~'), 0);
CHECK_EQ(mclib_isalnum(' '), 0);
CHECK_EQ(mclib_isalnum('\377'), 0);
END_TEST()

BEGIN_TEST(isblank__basic)
CHECK_NE(mclib_isblank(' '), 0);
CHECK_NE(mclib_isblank('\t'), 0);

CHECK_EQ(mclib_isblank('\n'), 0);
END_TEST()

BEGIN_TEST(iscntrl__basic)
CHECK_EQ(mclib_iscntrl(' '), 0);
CHECK_NE(mclib_iscntrl('\t'), 0);
END_TEST()

BEGIN_TEST(isdigit__basic)
CHECK_NE(mclib_isdigit('0'), 0);
CHECK_NE(mclib_isdigit('5'), 0);
CHECK_NE(mclib_isdigit('9'), 0);

CHECK_EQ(mclib_isdigit('A'), 0);
END_TEST()

#if 0
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
#endif

const struct UnitTestEntry kCtypeUnitTests[] = {{isalnum__basic, "isalnum: basic"},
                                                {isalpha__basic, "isalpha: basic"},
                                                {isblank__basic, "isblank: basic"},
                                                {iscntrl__basic, "iscntrl: basic"},
                                                {isdigit__basic, "isdigit: basic"},
                                                /*
                                                {isgraph__basic, "isgraph: basic"},
                                                {islower__basic, "islower: basic"},
                                                {isprint__basic, "isprint: basic"},
                                                {ispunct__basic, "ispunct: basic"},
                                                {isspace__basic, "isspace: basic"},
                                                {isupper__basic, "isupper: basic"},
                                                {isxdigit__basic, "isxdigit: basic"},
                                                {tolower__basic, "tolower: basic"},
                                                {toupper__basic, "toupper: basic"},
                                                 */
                                                {NULL, NULL}};
