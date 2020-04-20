#ifndef INCLUDE_METALC_WCHAR_H_
#define INCLUDE_METALC_WCHAR_H_

#include <metalc/metalc.h>
#include <metalc/stdint.h>

typedef uint32_t __mcint_wchar_t;

#ifndef METALC_COMPILE_FOR_TESTING
    typedef __mcint_wchar_t wchar_t;
#endif

#define WCHAR_MIN   0UL
#define WCHAR_MAX   0x10ffffUL


#endif  /* INCLUDE_METALC_WCHAR_H_ */
