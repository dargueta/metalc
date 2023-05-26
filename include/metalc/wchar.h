#ifndef INCLUDE_METALC_WCHAR_H_
#define INCLUDE_METALC_WCHAR_H_

#include "stddef.h"

typedef uint32_t mclib_wchar_t;


#ifndef METALC_COMPILE_FOR_TESTING
    typedef mclib_wchar_t wchar_t;
#endif

#define mclib_WCHAR_MIN   0UL
#define mclib_WCHAR_MAX   0x10ffffUL

#ifndef METALC_DISABLE_STDLIB_DEFS
    #define WCHAR_MIN mclib_WCHAR_MIN
    #define WCHAR_MAX mclib_WCHAR_MAX
#endif

#endif  /* INCLUDE_METALC_WCHAR_H_ */
