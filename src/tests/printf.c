#include <metalc/errno.h>
#include <metalc/internal/printf.h>
#include <metalc/string.h>
#include "testing.h"


BEGIN_TEST(format_spec__simple__d)
    struct MCFormatSpecifier info;
    int result;

    mclib_memset(&info, 0, sizeof(info));
    result = mcinternal_parse_printf_format_specifier("d", &info);
    CHECK_EQ(mclib_errno, 0);
    CHECK_EQ(result, 1);
    CHECK_EQ(info.justify, 0);
    CHECK_EQ(info.sign_representation, MCFMT_SIGN__ONLY_NEGATIVE);
END_TEST()


const struct UnitTestEntry kPrintfUnitTests[] = {
    {format_spec__simple__d, "printf: Analyze `%d`"},
    {NULL, NULL}
};
