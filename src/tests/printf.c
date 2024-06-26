#include "testing.h"
#include <metalc/errno.h>
#include <metalc/internal/printf.h>
#include <metalc/limits.h>
#include <metalc/stdio.h>
#include <metalc/string.h>

BEGIN_TEST(parse_printf_format_flags__empty)
struct MCFormatSpecifier info;
int result;

mclib_memset(&info, 0, sizeof(info));
result = parse_printf_format_flags(".02f", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 0);
CHECK_EQ(info.justify, MCFMT_JUSTIFY__UNSPECIFIED);
CHECK_EQ(info.sign_representation, MCFMT_SIGN__ONLY_NEGATIVE);
CHECK_EQ(info.has_radix_prefix, 0);
CHECK_EQ(info.is_zero_padded, 0);
END_TEST()

BEGIN_TEST(parse_printf_format_flags__left_align_zero)
struct MCFormatSpecifier info;
int result;

mclib_memset(&info, 0, sizeof(info));
result = parse_printf_format_flags("-05d", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 2);
CHECK_EQ(info.justify, MCFMT_JUSTIFY__LEFT);
CHECK_EQ(info.sign_representation, MCFMT_SIGN__ONLY_NEGATIVE);
CHECK_EQ(info.has_radix_prefix, 0);
CHECK_EQ(info.is_zero_padded, 1);
END_TEST()

BEGIN_TEST(parse_printf_format_width__empty)
struct MCFormatSpecifier info;
int result;

/* Deliberately not using memset() on `info` */
result = parse_printf_format_width("d", &info);

CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 0);
CHECK_EQ(info.minimum_field_width, 0);
END_TEST()

BEGIN_TEST(parse_printf_format_width__basic)
struct MCFormatSpecifier info;
int result;

/* Deliberately not using memset() on `info` */
result = parse_printf_format_width("6d", &info);

CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 1);
CHECK_EQ(info.minimum_field_width, 6);
END_TEST()

BEGIN_TEST(parse_printf_format_width__width_overflow)
struct MCFormatSpecifier info;
int result;

/* The width here should overflow (assuming an integer is 32 bits). The
 * result should be clamped to the largest representable integer. */
result = parse_printf_format_width("4294967295d", &info);

CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 10);
CHECK_EQ(info.minimum_field_width, INT_MAX);
END_TEST()

BEGIN_TEST(parse_printf_format_precision__empty)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_precision("", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 0);
CHECK_EQ(info.fraction_zero_padding, 0);
CHECK_EQ(info.fraction_precision, 0);
END_TEST()

BEGIN_TEST(parse_printf_format_precision__not_defined)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_precision("f", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 0);
CHECK_EQ(info.fraction_zero_padding, 0);
CHECK_EQ(info.fraction_precision, 0);
END_TEST()

BEGIN_TEST(parse_printf_format_precision__zero_padded)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_precision(".03f", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 3);
CHECK_EQ(info.fraction_zero_padding, 1);
CHECK_EQ(info.fraction_precision, 3);
END_TEST()

BEGIN_TEST(parse_printf_format_precision__not_zero_padded)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_precision(".149f", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 4);
CHECK_EQ(info.fraction_zero_padding, 0);
CHECK_EQ(info.fraction_precision, 149);
END_TEST()

BEGIN_TEST(parse_printf_format_type__d)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_type("d", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 1);
CHECK_EQ(info.argument_type, MCFMT_ARGT__INT);
CHECK_EQ(info.argument_width, MCFMT_ARGW__DEFAULT);
CHECK_EQ(info.is_unsigned, 0);
CHECK_EQ(info.use_uppercase, 0);
CHECK_EQ(info.radix, 10);
END_TEST()

BEGIN_TEST(parse_printf_format_type__hu)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_type("hu", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 2);
CHECK_EQ(info.argument_type, MCFMT_ARGT__SHORT);
CHECK_EQ(info.argument_width, MCFMT_ARGW__SHORT);
CHECK_EQ(info.is_unsigned, 1);
CHECK_EQ(info.use_uppercase, 0);
CHECK_EQ(info.radix, 10);
END_TEST()

BEGIN_TEST(parse_printf_format_type__hhX)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_type("hhX", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 3);
CHECK_EQ(info.argument_type, MCFMT_ARGT__BYTE);
CHECK_EQ(info.argument_width, MCFMT_ARGW__BYTE);
CHECK_EQ(info.use_uppercase, 1);
CHECK_EQ(info.radix, 16);
END_TEST()

BEGIN_TEST(parse_printf_format_type__A)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_type("A", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 1);
CHECK_EQ(info.argument_type, MCFMT_ARGT__DOUBLE);
CHECK_EQ(info.argument_width, MCFMT_ARGW__DEFAULT);
CHECK_EQ(info.use_uppercase, 1);
CHECK_EQ(info.radix, 16);
END_TEST()

BEGIN_TEST(parse_printf_format_type__a)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_type("a", &info);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 1);
CHECK_EQ(info.argument_type, MCFMT_ARGT__DOUBLE);
CHECK_EQ(info.argument_width, MCFMT_ARGW__DEFAULT);
CHECK_EQ(info.use_uppercase, 0);
CHECK_EQ(info.radix, 16);
END_TEST()

BEGIN_TEST(parse_printf_format_type__unexpected_eos)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_type("", &info);
CHECK_EQ(mclib_errno, mclib_EINVAL);
CHECK_EQ(result, -1);
END_TEST()

BEGIN_TEST(parse_printf_format_specifier__simple__d)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_specifier("d", &info);
CHECK_EQ(result, 1);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(info.justify, MCFMT_JUSTIFY__UNSPECIFIED);
CHECK_EQ(info.sign_representation, MCFMT_SIGN__ONLY_NEGATIVE);
CHECK_EQ(info.argument_type, MCFMT_ARGT__INT);
CHECK_EQ(info.argument_width, MCFMT_ARGW__DEFAULT);
CHECK_EQ(info.minimum_field_width, 0);
CHECK_EQ(info.radix, 10);
CHECK_EQ(info.is_unsigned, 0);
CHECK_EQ(info.is_zero_padded, 0);
CHECK_EQ(info.has_radix_prefix, 0);
CHECK_EQ(info.use_scientific_notation, MCFMT_SCINOT__UNSPECIFIED);
CHECK_EQ(info.fraction_zero_padding, 0);
CHECK_EQ(info.fraction_precision, 0);
CHECK_EQ(info.use_uppercase, 0);
END_TEST()

BEGIN_TEST(parse_printf_format_specifier__03hu)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_specifier("03hu", &info);
CHECK_EQ(result, 4);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(info.justify, 0);
CHECK_EQ(info.sign_representation, MCFMT_SIGN__ONLY_NEGATIVE);
CHECK_EQ(info.argument_type, MCFMT_ARGT__SHORT);
CHECK_EQ(info.argument_width, MCFMT_ARGW__SHORT);
CHECK_EQ(info.minimum_field_width, 3);
CHECK_EQ(info.radix, 10);
CHECK_EQ(info.is_unsigned, 1);
CHECK_EQ(info.is_zero_padded, 1);
CHECK_EQ(info.has_radix_prefix, 0);
CHECK_EQ(info.use_scientific_notation, MCFMT_SCINOT__UNSPECIFIED);
CHECK_EQ(info.fraction_zero_padding, 0);
CHECK_EQ(info.fraction_precision, 0);
CHECK_EQ(info.use_uppercase, 0);
END_TEST()

BEGIN_TEST(sprintf_basic)
char buffer[16];
int result;

result = mclib_snprintf(buffer, 16, "%d", 15903);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(result, 6);
INFO_MSG("Buffer contents: `%s`", buffer);
CHECK_EQ(mclib_memcmp(buffer, "15903", result), 0);
END_TEST()

#if METALC_COMPILE_OPTION_ENABLE_LONGLONG
BEGIN_TEST(parse_printf_format_specifier__304Le)
struct MCFormatSpecifier info;
int result;

result = parse_printf_format_specifier("-+3.04Le", &info);
CHECK_EQ(result, 8);
CHECK_EQ(mclib_errno, 0);
CHECK_EQ(info.justify, MCFMT_JUSTIFY__LEFT);
CHECK_EQ(info.sign_representation, MCFMT_SIGN__FORCE_POSITIVE);
CHECK_EQ(info.argument_type, MCFMT_ARGT__LONGDOUBLE);
CHECK_EQ(info.argument_width, MCFMT_ARGW__LONG_DOUBLE);
CHECK_EQ(info.minimum_field_width, 3);
CHECK_EQ(info.radix, 10);
CHECK_EQ(info.is_unsigned, 0);
CHECK_EQ(info.is_zero_padded, 0);
CHECK_EQ(info.has_radix_prefix, 0);
CHECK_EQ(info.use_scientific_notation, MCFMT_SCINOT__ALWAYS);
CHECK_EQ(info.fraction_zero_padding, 1);
CHECK_EQ(info.fraction_precision, 4);
CHECK_EQ(info.use_uppercase, 0);
END_TEST()
#endif

const struct UnitTestEntry kPrintfUnitTests[] = {
    {parse_printf_format_flags__empty, "printf: alignment flags, empty string"},
    {parse_printf_format_flags__left_align_zero, "printf: alignment flags, `%-05d`"},
    {parse_printf_format_width__empty, "printf: width flags, `%d`"},
    {parse_printf_format_width__basic, "printf: width flags, `%05d`"},
    {parse_printf_format_width__width_overflow,
     "printf: width flags overflow 32-bit int"},
    {parse_printf_format_precision__empty,
     "printf: floating-point precision, empty string"},
    {parse_printf_format_precision__not_defined,
     "printf: floating-point precision, not defined"},
    {parse_printf_format_precision__zero_padded,
     "printf: floating-point precision, `%.03f`"},
    {parse_printf_format_precision__not_zero_padded,
     "printf: floating-point precision, `%.149f`"},
    {parse_printf_format_type__d, "printf: type: `%d`"},
    {parse_printf_format_type__hu, "printf: type: `%hu`"},
    {parse_printf_format_type__hhX, "printf: type: `%hu`"},
    {parse_printf_format_type__a, "printf: type: `%a`"},
    {parse_printf_format_type__A, "printf: type: `%A`"},
    {parse_printf_format_type__unexpected_eos,
     "printf: type: invalid `%` at end of string"},
    {parse_printf_format_specifier__simple__d, "printf: Analyze `%d`"},
    {parse_printf_format_specifier__03hu, "printf: Analyze `%03hu`"},
#if METALC_COMPILE_OPTION_ENABLE_LONGLONG
    {parse_printf_format_specifier__304Le, "printf: Analyze `%-+3.04Le`"},
#endif
    {sprintf_basic, "sprintf: basic"},
    {NULL, NULL}};
