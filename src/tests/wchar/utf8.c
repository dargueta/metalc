#include "../testing.h"
#include <metalc/stdlib.h>


extern int mcinternal_utf8_mblen(const char *str, size_t n);
extern int mcinternal_utf8_mbtowc(mclib_wchar_t *pwc, const char *str, size_t n);
extern int mcinternal_utf8_wctomb(char *str, mclib_wchar_t wchar);


BEGIN_TEST(mblen__empty_string_1)
    int length = mcinternal_utf8_mblen("", 1);
    ASSERT(length == 0);
END_TEST()


const struct UnitTestEntry kWcharUtf8UnitTests[] = {
        {mblen__empty_string_1, "mblen: empty string"},
        {NULL, NULL}
};
