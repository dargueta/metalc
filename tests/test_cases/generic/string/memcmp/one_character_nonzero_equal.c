#include <metalc/string.h>
#include "testing.h"


BEGIN_TEST()
    check(memcmp("A", "A", 1) == 0);
END_TEST()
