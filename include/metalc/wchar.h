#ifndef INCLUDE_METALC_WCHAR_H_
#define INCLUDE_METALC_WCHAR_H_

#include "metalc.h"
#include "stdint.h"


typedef uint_least32_t mclib_wchar_t;

#define mclib_WCHAR_MIN   0UL
#define mclib_WCHAR_MAX   0x10ffffUL

#ifndef METALC_CURRENTLY_COMPILING_LIBRARY
    typedef mclib_wchar_t wchar_t;
    #define WCHAR_MIN mclib_WCHAR_MIN
    #define WCHAR_MAX mclib_WCHAR_MAX
#endif

#endif  /* INCLUDE_METALC_WCHAR_H_ */
