#ifndef INCLUDE_METALC_MATH_H_
#define INCLUDE_METALC_MATH_H_

#include "metalc.h"


METALC_API_EXPORT_ASM double mclib_cos(double x);
METALC_API_EXPORT_ASM float mclib_cosf(float x);
METALC_API_EXPORT_ASM double mclib_sin(double x);
METALC_API_EXPORT_ASM float mclib_sinf(float x);
METALC_API_EXPORT_ASM double mclib_tan(double x);
METALC_API_EXPORT_ASM float mclib_tanf(float x);
METALC_API_EXPORT_ASM double mclib_pow(double base, double exponent);
METALC_API_EXPORT_ASM float mclib_powf(float base, float exponent);
METALC_API_EXPORT_ASM double mclib_fabs(double x);
METALC_API_EXPORT_ASM float mclib_fabsf(float x);
METALC_API_EXPORT_ASM double mclib_asin(double x);
METALC_API_EXPORT_ASM float mclib_asinf(float x);
METALC_API_EXPORT_ASM double mclib_acos(double x);
METALC_API_EXPORT_ASM float mclib_acosf(float x);

#if METALC_HAVE_LONG_DOUBLE
    METALC_API_EXPORT_ASM long double mclib_cosl(long double x);
    METALC_API_EXPORT_ASM long double mclib_sinl(long double x);
    METALC_API_EXPORT_ASM long double mclib_tanl(long double x);
    METALC_API_EXPORT_ASM long double mclib_powl(long double base, long double exponent);
    METALC_API_EXPORT_ASM long double mclib_fabsl(long double x);
    METALC_API_EXPORT_ASM long double mclib_asinl(long double x);
    METALC_API_EXPORT_ASM long double mclib_acosl(long double x);
#endif

#endif  /* INCLUDE_METALC_MATH_H_ */
