#include <metalc/string.h>
#include "testing.h"


BEGIN_TEST()
    check(memcmp("", "", 1) == 0);
END_TEST()
