#ifndef INCLUDE_METALC_ASSERT_H_
#define INCLUDE_METALC_ASSERT_H_

#include "metalc.h"

#ifdef NDEBUG
    #define __mcapi_assert(expression)
#else
    #define __mcapi_assert(expression)  __mcint_assert((expression), __LINE__, __FILE__, #expression, NULL)
#endif


#ifndef METALC_DISABLE_STDLIB_DEFS
    #define assert  __mcapi_assert
#endif


METALC_API_INTERAL_WITH_ATTR(nonnull(3, 4))
void __mcint_assert(
    int expression, int line, const char *file, const char* assert_text,
    const char *message, ...
);

#endif  /* INCLUDE_METALC_ASSERT_H_ */
