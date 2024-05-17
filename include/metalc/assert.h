#ifndef INCLUDE_METALC_ASSERT_H_
#define INCLUDE_METALC_ASSERT_H_

#include "metalc.h"

#ifdef NDEBUG
#    define mclib_assert(expression)
#else
#    define mclib_assert(expression)                                                     \
        mcinternal_assert((expression), __LINE__, __FILE__, #expression, NULL)
#endif

#ifndef METALC_DISABLE_STDLIB_DEFS
#    define assert(expression) mclib_assert(expression)
#endif

METALC_INTERNAL_ONLY
METALC_ATTR__NONNULL_ARGS(3, 4)
void mcinternal_assert(int expression, int line, const char *file,
                       const char *assert_text, const char *message, ...);

#endif /* INCLUDE_METALC_ASSERT_H_ */
