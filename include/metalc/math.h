#ifndef INCLUDE_METALC_MATH_H_
#define INCLUDE_METALC_MATH_H_

#include "metalc.h"


METALC_API_EXPORT_ASM double __mcapi_cos(double x);
METALC_API_EXPORT_ASM float __mcapi_cosf(float x);
METALC_API_EXPORT_ASM double __mcapi_sin(double x);
METALC_API_EXPORT_ASM float __mcapi_sinf(float x);
METALC_API_EXPORT_ASM double __mcapi_tan(double x);
METALC_API_EXPORT_ASM float __mcapi_tanf(float x);
METALC_API_EXPORT_ASM double __mcapi_pow(double base, double exponent);
METALC_API_EXPORT_ASM float __mcapi_powf(float base, float exponent);
METALC_API_EXPORT_ASM double __mcapi_fabs(double x);
METALC_API_EXPORT_ASM float __mcapi_fabsf(float x);
METALC_API_EXPORT_ASM double __mcapi_asin(double x);
METALC_API_EXPORT_ASM float __mcapi_asinf(float x);
METALC_API_EXPORT_ASM double __mcapi_acos(double x);
METALC_API_EXPORT_ASM float __mcapi_acosf(float x);

#if METALC_HAVE_LONG_DOUBLE
    METALC_API_EXPORT_ASM long double __mcapi_cosl(long double x);
    METALC_API_EXPORT_ASM long double __mcapi_sinl(long double x);
    METALC_API_EXPORT_ASM long double __mcapi_tanl(long double x);
    METALC_API_EXPORT_ASM long double __mcapi_powl(long double base, long double exponent);
    METALC_API_EXPORT_ASM long double __mcapi_fabsl(long double x);
    METALC_API_EXPORT_ASM long double __mcapi_asinl(long double x);
    METALC_API_EXPORT_ASM long double __mcapi_acosl(long double x);
#endif

#endif  /* INCLUDE_METALC_MATH_H_ */
