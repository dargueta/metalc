#ifndef INCLUDE_METALC_ASSERT_H_
#define INCLUDE_METALC_ASSERT_H_

#include "metalc.h"

#ifdef NDEBUG
    #define assert(expression)
#else
    #define assert(expression)  __mcint_assert((expression), __LINE__, __FILE__, #expression, NULL)
#endif


METALC_API_INTERAL_WITH_ATTR(nonnull(3, 4))
void __mcint_assert(
    int expression, int line, const char *file, const char* assert_text,
    const char *message, ...
);

#endif  /* INCLUDE_METALC_ASSERT_H_ */
