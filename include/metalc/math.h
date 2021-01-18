#ifndef INCLUDE_METALC_MATH_H_
#define INCLUDE_METALC_MATH_H_

#include "metalc.h"


METALC_API_EXPORT_ASM double cos(double x);
METALC_API_EXPORT_ASM float cosf(float x);
METALC_API_EXPORT_ASM double sin(double x);
METALC_API_EXPORT_ASM float sinf(float x);
METALC_API_EXPORT_ASM double tan(double x);
METALC_API_EXPORT_ASM float tanf(float x);
METALC_API_EXPORT_ASM double pow(double base, double exponent);
METALC_API_EXPORT_ASM float powf(float base, float exponent);
METALC_API_EXPORT_ASM double fabs(double x);
METALC_API_EXPORT_ASM float fabsf(float x);
METALC_API_EXPORT_ASM double asin(double x);
METALC_API_EXPORT_ASM float asinf(float x);
METALC_API_EXPORT_ASM double acos(double x);
METALC_API_EXPORT_ASM float acosf(float x);

#if METALC_HAVE_LONG_DOUBLE
    METALC_API_EXPORT_ASM long double cosl(long double x);
    METALC_API_EXPORT_ASM long double sinl(long double x);
    METALC_API_EXPORT_ASM long double tanl(long double x);
    METALC_API_EXPORT_ASM long double powl(long double base, long double exponent);
    METALC_API_EXPORT_ASM long double fabsl(long double x);
    METALC_API_EXPORT_ASM long double asinl(long double x);
    METALC_API_EXPORT_ASM long double acosl(long double x);
#endif

#endif  /* INCLUDE_METALC_MATH_H_ */
