#include "../testing.h"
#include <metalc/errno.h>
#include <metalc/stdlib.h>

extern int mcinternal_utf8_mblen(const char *str, size_t n);
extern int mcinternal_utf8_mbtowc(mclib_wchar_t *pwc, const char *str, size_t n);
extern int mcinternal_utf8_wctomb(char *str, mclib_wchar_t wchar);

BEGIN_TEST(mblen_utf8__not_stateful)
/* If the string pointer is null the length shouldn't matter. */
CHECK(!mcinternal_utf8_mblen(NULL, 0));
CHECK(!mcinternal_utf8_mblen(NULL, 123));
END_TEST()

BEGIN_TEST(mblen_utf8__invalid_n)
CHECK_EQ(mcinternal_utf8_mblen("something", 0), -1);
CHECK_EQ(mclib_errno, mclib_EINVAL);
END_TEST()

BEGIN_TEST(mblen_utf8__null)
int length = mcinternal_utf8_mblen("", 1);
CHECK_EQ(length, 0);
END_TEST()

BEGIN_TEST(mblen_utf8__disregard_subsequent_chars)
int length = mcinternal_utf8_mblen("\xc3\xa1!!!", 6);
CHECK_EQ(length, 2);
END_TEST()

BEGIN_TEST(mblen_utf8__bmp_hindi_ka)
int length = mcinternal_utf8_mblen("\xe0\xa4\x95", 4);
CHECK_EQ(length, 3);
END_TEST()

BEGIN_TEST(mblen_utf8__shrug_emoji)
int length = mcinternal_utf8_mblen("\xf0\x9f\xa4\xb7\x0a", 6);
CHECK_EQ(length, 4);
END_TEST()

BEGIN_TEST(mblen_utf8__ascii)
int length = mcinternal_utf8_mblen("\x7f\xf0\x9f\xa4\xb7", 6);
CHECK_EQ(length, 1);
END_TEST()

BEGIN_TEST(mblen_utf8__ilseq)
int length = mcinternal_utf8_mblen("\xff", 2);
CHECK_EQ(length, -1);
CHECK_EQ(mclib_errno, mclib_EILSEQ);
END_TEST()

const struct UnitTestEntry kWcharUtf8UnitTests[] = {
    {mblen_utf8__not_stateful, "mblen [UTF_8]: codec is not stateful"},
    {mblen_utf8__invalid_n, "mblen [UTF_8]: invalid value for `n` sets errno"},
    {mblen_utf8__null, "mblen [UTF_8]: null character has length 1"},
    {mblen_utf8__disregard_subsequent_chars, "mblen [UTF_8]: Ignore trailing characters"},
    {mblen_utf8__bmp_hindi_ka, "mblen [UTF_8]: Basic Multilingual Plane, Hindi \"Ka\""},
    {mblen_utf8__shrug_emoji, "mblen [UTF_8]: Shrug emoji length is 4"},
    {mblen_utf8__ascii, "mblen [UTF_8]: ASCII character length is 1"},
    {mblen_utf8__ilseq, "mblen [UTF_8]: 0xFF is illegal"},
    {NULL, NULL}};
