#ifndef INCLUDE_METALC_ASSERT_H_
#define INCLUDE_METALC_ASSERT_H_

#include <metalc/metalc.h>

#ifdef NDEBUG
    #define assert(expression)  (expression)
#else
    #define assert(expression)  _internal_assert(expression, __LINE__, __FUNCTION__, __FILE__)
#endif

METALC_API_EXPORT void _internal_assert(int expression, int line, const char *function, const char *file);

#endif  /* INCLUDE_METALC_ASSERT_H_ */
