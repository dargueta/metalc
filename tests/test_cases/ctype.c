#include <metalc/ctype.h>
#include <metalc/stddef.h>

#include "../include/testing.h"


BEGIN_TEST()
    check(isalnum('A') != 0);
    check(isalnum('F') != 0);
    check(isalnum('Z') != 0);
    check(isalnum('a') != 0);
    check(isalnum('j') != 0);
    check(isalnum('z') != 0);
    check(isalnum('0') != 0);
    check(isalnum('9') != 0);

    check(isalnum('\0') == 0);
    check(isalnum('~') == 0);
    check(isalnum(' ') == 0);
    check(isalnum('\377') == 0);
    check(isalnum('{') == 0);
    check(isalnum('}') == 0);
END_TEST()


BEGIN_TEST()
    check(isalnum('A') != 0);
    check(isalnum('N') != 0);
    check(isalnum('q') != 0);
    check(isalnum('r') != 0);

    check(isalnum('\0') == 0);
    check(isalnum('~') == 0);
    check(isalnum(' ') == 0);
    check(isalnum('\377') == 0);
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
END_TEST()


BEGIN_TEST()
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
