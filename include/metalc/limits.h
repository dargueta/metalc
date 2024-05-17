#ifndef INCLUDE_METALC_LIMITS_H_
#define INCLUDE_METALC_LIMITS_H_

#include "metalc.h"

#if METALC_HAVE_LIMITS_H
#    include <limits.h>
#else
#    error "Compiler must provide required header `limits.h` but it doesn't."
#endif /* METALC_HAVE_LIMITS_H */

#endif /* INCLUDE_METALC_LIMITS_H_ */
