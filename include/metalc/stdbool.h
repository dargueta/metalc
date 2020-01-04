#ifndef INCLUDE_METALC_STDBOOL_H_
#define INCLUDE_METALC_STDBOOL_H_

#include <metalc/metalc.h>

#if METALC_HAVE_STDBOOL_H
    /* Always defer to the compiler-provided header if possible. */
    #include <stdbool.h>
#else
    typedef int bool;
    #define true    1
    #define false   0
#endif  /* METALC_HAVE_STDBOOL_H */

#endif  /* INCLUDE_METALC_STDBOOL_H_ */
