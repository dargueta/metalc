#ifndef INCLUDE_METALC_WCHAR_H_
#define INCLUDE_METALC_WCHAR_H_

#include <metalc/metalc.h>
#include <metalc/stdint.h>


typedef uint32_t __mcapi_wchar_t;


#ifndef METALC_COMPILE_FOR_TESTING
    typedef __mcapi_wchar_t wchar_t;
#endif

#define __mcapi_WCHAR_MIN   0UL
#define __mcapi_WCHAR_MAX   0x10ffffUL

#ifndef METALC_DISABLE_STDLIB_DEFS
    #define WCHAR_MIN __mcapi_WCHAR_MIN
    #define WCHAR_MAX __mcapi_WCHAR_MAX
#endif

#endif  /* INCLUDE_METALC_WCHAR_H_ */
