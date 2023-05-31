#include <metalc/string.h>
#include "testing.h"


BEGIN_TEST()
    check(memcmp("", "", 0) == 0);
END_TEST()
