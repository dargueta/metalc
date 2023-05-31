#include <metalc/string.h>
#include "testing.h"


BEGIN_TEST()
static const char *str = "Th\nisIsAString";
check(memchr(str, '\n', 5) == str + 2);
END_TEST()
