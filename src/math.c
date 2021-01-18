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


double fabs(double x) {
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


float fabsf(float x) {
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


double cos(double x) {
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
                cosine -= pow(x, 2 * i) / _factorial(2 * i);
            else
                cosine += pow(x, 2 * i) / _factorial(2 * i);
        }

        return cosine;
    #endif
}


float cosf(float x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fcos" : "st0");
        #else
            __asm fcos;
        #endif
    #else
        /* This is a cheap copout. :/ */
        return (float)cos((double)x);
    #endif
}


double sin(double x) {
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
                sine -= pow(x, (2 * i) + 1) / _factorial((2 * i) + 1);
            else
                sine += pow(x, (2 * i) + 1) / _factorial((2 * i) + 1);
        }

        return sine;
    #endif
}


float sinf(float x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fsin" : "st0");
        #else
            __asm fsin;
        #endif
    #else
        return (float)sin((double)x);
    #endif
}


double tan(double x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fptan\nfincstp" : "st0");
        #else
            __asm fptan;
            __asm fincstp;
        #endif
    #else
        if (fabs(x) > _PI_OVER_2) {
            errno = EDOM;
            return 0;
        }
        return sin(x) / cos(x);
    #endif
}


float tanf(float x) {
    #if 0  /* #if METALC_ENABLE_ASM_IMPLEMENTATIONS */
        #if METALC_COMPILER_GCC_COMPATIBLE
            __asm__ ("fptan\nfincstp" : "st0");
        #else
            __asm fptan;
            __asm fincstp;
        #endif
    #else
        if (fabsf(x) > _PI_OVER_2) {
            errno = EDOM;
            return 0;
        }
        return sinf(x) / cosf(x);
    #endif
}


double asin(double x) {
    unsigned i;
    double result = 0;

    if (fabs(x) > 1) {
        errno = EDOM;
        return 0;
    }

    /* From https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Infinite_series */
    for (i = 0; i < LOOP_PRECISION; ++i) {
        result += \
            _factorial(2 * i) * pow(x, (2 * i) + 1)
            / pow(pow(2, i) * _factorial(i), 2) / ((2 * i) + 1);
    }
    return result;
}


float asinf(float x) {
    return (float)asin((double)x);
}


double acos(double x) {
    return _PI_OVER_2 - asin(x);
}


float acosf(float x) {
    return _PI_OVER_2 - asin((double)x);
}


double pow(double base, double exponent) {
    if (exponent == 0)
        return 1.0;
    else if (exponent == 1)
        return base;
    else if (exponent > 1) {
        /* Multiply */
        errno = ENOSYS;
        return 0;
    }
    else if (exponent < 0)
        return 1 / pow(base, -exponent);
    else {
        /* Exponent is between 0 and 1, exclusive */
        errno = ENOSYS;
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
    long double fabsl(long double x) {
        if (x < 0)
            return -x;
        return x;
    }

    long double cosl(long double x) {
        unsigned i;
        long double cosine = 1.0;

        for (i = 0; i < LOOP_PRECISION; ++i) {
            if (i % 2 == 1)
                cosine -= powl(x, 2 * i) / _factorial(2 * i);
            else
                cosine += powl(x, 2 * i) / _factorial(2 * i);
        }
        return cosine;
    }


    long double sinl(long double x) {
        unsigned i;
        long double sine = x;

        for (i = 0; i < LOOP_PRECISION; ++i) {
            if (i % 2 == 1)
                sine -= powl(x, (2 * i) + 1) / _factorial((2 * i) + 1);
            else
                sine += powl(x, (2 * i) + 1) / _factorial((2 * i) + 1);
        }

        return sine;
    }


    long double tanl(long double x) {
        if (fabsl(x) > _PI_OVER_2) {
            errno = EDOM;
            return 0;
        }
        return sinl(x) / cosl(x);
    }

    long double asinl(long double x) {
        unsigned i;
        long double result = 0;

        if (fabsl(x) > 1) {
            errno = EDOM;
            return 0;
        }

        /* From https://en.wikipedia.org/wiki/Inverse_trigonometric_functions#Infinite_series */
        for (i = 0; i < LOOP_PRECISION; ++i) {
            result += \
                _factorial(2 * i) * powl(x, (2 * i) + 1)
                / powl(powl(2, i) * _factorial(i), 2) / ((2 * i) + 1);
        }
        return result;
    }

    long double acosl(long double x) {
        return _PI_OVER_2 - asinl(x);
    }


    long double powl(long double base, long double exponent) {
        if (exponent == 0)
            return 1.0;
        else if (exponent == 1)
            return base;
        else if (exponent > 1) {
            /* Multiply */
            errno = ENOSYS;
            return 0;
        }
        else if (exponent < 0)
            return 1 / powl(base, -exponent);
        else {
            /* Exponent is between 0 and 1, exclusive */
            errno = ENOSYS;
            return 0;
        }
    }
#endif

#undef LOOP_PRECISION
#undef FACTORIAL_TABLE_ENTRIES
