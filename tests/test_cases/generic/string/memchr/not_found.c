#include <metalc/string.h>
#include "testing.h"


BEGIN_TEST()
    check(memchr("", '\n', 5) == NULL);
END_TEST()
