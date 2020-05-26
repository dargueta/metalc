/**
 * These are pretty inefficient. Yes, they could be implemented in assembly
 * language, and eventually they will, but doing it in C doesn't require worrying
 * about the ABI. Good enough for a first pass.
 */

#include "metalc/errno.h"
#include "metalc/float.h"
#include "metalc/math.h"


#define LOOP_PRECISION  6
#define FACTORIAL_TABLE_ENTRIES     22


#if METALC_HAVE_LONG_DOUBLE
    typedef long double metalc_big_float;
#else
    typedef double metalc_big_float;
#endif


/* Ratio taken from the Wikipedia article on pi */
static const metalc_big_float _PI = 245850922.0 / 78256779.0;
static const metalc_big_float _PI_OVER_2 = _PI / 2.0;

/* A precomputed table of the lowest factorial numbers to speed up computation
 * of sines, cosines, etc. To get the performance benefit this must have at least
 * (2 * (LOOP_PRECISION - 1)) + 1 entries. */
static const metalc_big_float kFactorialTable[FACTORIAL_TABLE_ENTRIES] = {
    /* 0! - 4! */
    1, 1, 2, 6, 24,
    /* 5! - 9! */
    120, 720, 5040, 40320, 362880,
    /* 10! - 14!*/
    3628800, 39916800, 479001600, 6227020800, 87178291200,
    /* 15! - 19! */
    1307674368000, 20922789888000, 355687428096000, 6402373705728000,
    121645100408832000,
    /* 20! - 21! */
    2432902008176640000.0, 51090942171709440000.0
};


static metalc_big_float _factorial(unsigned int n) {
    unsigned int i;
    metalc_big_float result;

    if (n < FACTORIAL_TABLE_ENTRIES)
        return kFactorialTable[n];

    result = kFactorialTable[FACTORIAL_TABLE_ENTRIES - 1];
    for (i = n; i > FACTORIAL_TABLE_ENTRIES - 1; --i)
        result *= i;

    return result;
}


double __mcapi_fabs(double x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fabs" : "st0");
        #else
            __asm fabs;
        #endif
    #else
        if (x < 0)
            return -x;
        return x;
    #endif
}


float __mcapi_fabsf(float x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fabs" : "st0");
        #else
            __asm fabs;
        #endif
    #else
        if (x < 0)
            return -x;
        return x;
    #endif
}


double __mcapi_cos(double x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fcos" : "st0");
        #else
            __asm fcos;
        #endif
    #else
        unsigned i;
        double cosine = 1.0;

        for (i = 0; i < LOOP_PRECISION; ++i) {
            if (i % 2 == 1)
                cosine -= __mcapi_pow(x, 2 * i) / _factorial(2 * i);
            else
                cosine += __mcapi_pow(x, 2 * i) / _factorial(2 * i);
        }

        return cosine;
    #endif
}


float __mcapi_cosf(float x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fcos" : "st0");
        #else
            __asm fcos;
        #endif
    #else
        /* This is a cheap copout. :/ */
        return (float)__mcapi_cos((double)x);
    #endif
}


double __mcapi_sin(double x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fsin" : "st0");
        #else
            __asm fsin;
        #endif
    #else
        unsigned i;
        double sine = x;

        for (i = 0; i < LOOP_PRECISION; ++i) {
            if (i % 2 == 1)
                sine -= __mcapi_pow(x, (2 * i) + 1) / _factorial((2 * i) + 1);
            else
                sine += __mcapi_pow(x, (2 * i) + 1) / _factorial((2 * i) + 1);
        }

        return sine;
    #endif
}


float __mcapi_sinf(float x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fsin" : "st0");
        #else
            __asm fsin;
        #endif
    #else
        return (float)__mcapi_sin((double)x);
    #endif
}


double __mcapi_tan(double x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fptan\nfincstp" : "st0");
        #else
            __asm fptan;
            __asm fincstp;
        #endif
    #else
        if (__mcapi_fabs(x) > _PI_OVER_2) {
            __mcapi_errno = __mcapi_EDOM;
            return 0;
        }
        return __mcapi_sin(x) / __mcapi_cos(x);
    #endif
}


float __mcapi_tanf(float x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fptan\nfincstp" : "st0");
        #else
            __asm fptan;
            __asm fincstp;
        #endif
    #else
        if (__mcapi_fabsf(x) > _PI_OVER_2) {
            __mcapi_errno = __mcapi_EDOM;
            return 0;
        }
        return __mcapi_sinf(x) / __mcapi_cosf(x);
    #endif
}


double __mcapi_asin(double x) {
    unsigned i;
    double result = 0;

    if (__mcapi_fabs(x) > 1) {
        __mcapi_errno = __mcapi_EDOM;
        return 0;
    }

    /* From https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Infinite_series */
    for (i = 0; i < LOOP_PRECISION; ++i) {
        result += \
            _factorial(2 * i) * __mcapi_pow(x, (2 * i) + 1)
            / __mcapi_pow(__mcapi_pow(2, i) * _factorial(i), 2) / ((2 * i) + 1);
    }
    return result;
}


float __mcapi_asinf(float x) {
    return (float)__mcapi_asin((double)x);
}


double __mcapi_acos(double x) {
    return _PI_OVER_2 - __mcapi_asin(x);
}


float __mcapi_acosf(float x) {
    return _PI_OVER_2 - __mcapi_asin((double)x);
}


double __mcapi_pow(double base, double exponent) {
    if (exponent == 0)
        return 1.0;
    else if (exponent == 1)
        return base;
    else if (exponent > 1) {
        /* Multiply */
        __mcapi_errno = __mcapi_ENOSYS;
        return 0;
    }
    else if (exponent < 0)
        return 1 / __mcapi_pow(base, -exponent);
    else {
        /* Exponent is between 0 and 1, exclusive */
        __mcapi_errno = __mcapi_ENOSYS;
        return 0;
    }
}


/* NOTE: Assembly language isn't supported for long doubles yet because their size
 * can change based on compiler flags and the architecture being compiled for.
 *
 * For example, with GCC: on 32-bit architectures a `long double` is 96 bits by
 * default, but can be extended to 128. On 64-bit architectures, `long double`
 * is 128 bits by default. Theoretically. Manual testing has shown its sizeof
 * returns 10 bytes by default on a 64-bit architecture.
 */
#if METALC_HAVE_LONG_DOUBLE
    long double __mcapi_fabsl(long double x) {
        if (x < 0)
            return -x;
        return x;
    }

    long double __mcapi_cosl(long double x) {
        unsigned i;
        long double cosine = 1.0;

        for (i = 0; i < LOOP_PRECISION; ++i) {
            if (i % 2 == 1)
                cosine -= __mcapi_powl(x, 2 * i) / _factorial(2 * i);
            else
                cosine += __mcapi_powl(x, 2 * i) / _factorial(2 * i);
        }
        return cosine;
    }


    long double __mcapi_sinl(long double x) {
        unsigned i;
        long double sine = x;

        for (i = 0; i < LOOP_PRECISION; ++i) {
            if (i % 2 == 1)
                sine -= __mcapi_powl(x, (2 * i) + 1) / _factorial((2 * i) + 1);
            else
                sine += __mcapi_powl(x, (2 * i) + 1) / _factorial((2 * i) + 1);
        }

        return sine;
    }


    long double __mcapi_tanl(long double x) {
        if (__mcapi_fabsl(x) > _PI_OVER_2) {
            __mcapi_errno = __mcapi_EDOM;
            return 0;
        }
        return __mcapi_sinl(x) / __mcapi_cosl(x);
    }

    long double __mcapi_asinl(long double x) {
        unsigned i;
        long double result = 0;

        if (__mcapi_fabsl(x) > 1) {
            __mcapi_errno = __mcapi_EDOM;
            return 0;
        }

        /* From https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Infinite_series */
        for (i = 0; i < LOOP_PRECISION; ++i) {
            result += \
                _factorial(2 * i) * __mcapi_powl(x, (2 * i) + 1)
                / __mcapi_powl(__mcapi_powl(2, i) * _factorial(i), 2) / ((2 * i) + 1);
        }
        return result;
    }

    long double __mcapi_acosl(long double x) {
        return _PI_OVER_2 - __mcapi_asinl(x);
    }


    long double __mcapi_powl(long double base, long double exponent) {
        if (exponent == 0)
            return 1.0;
        else if (exponent == 1)
            return base;
        else if (exponent > 1) {
            /* Multiply */
            __mcapi_errno = __mcapi_ENOSYS;
            return 0;
        }
        else if (exponent < 0)
            return 1 / __mcapi_powl(base, -exponent);
        else {
            /* Exponent is between 0 and 1, exclusive */
            __mcapi_errno = __mcapi_ENOSYS;
            return 0;
        }
    }
#endif

#undef LOOP_PRECISION
#undef FACTORIAL_TABLE_ENTRIES
