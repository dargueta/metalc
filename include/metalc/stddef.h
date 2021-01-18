#ifndef INCLUDE_METALC_STDDEF_H_
#define INCLUDE_METALC_STDDEF_H_

#include "metalc.h"
#include "stdint.h"


#if defined(INT_LEAST64_MAX)
    typedef uint_least64_t size_t;
    typedef int_least64_t ssize_t;
#elif defined(INT_LEAST32_MAX)
    typedef uint_least32_t size_t;
    typedef int_least32_t ssize_t;
#else
    typedef uint_least16_t size_t;
    typedef int_least16_t ssize_t;
#endif

/* TODO (dargueta): Is this correct? */
typedef intmax_t max_align_t;


#define offsetof(type, member)  ((size_t)(&(((type *)0)->(member))))


typedef uint_least32_t wchar_t;

#define WCHAR_MIN   0
#define WCHAR_MAX   UINT_LEAST32_MAX


#endif  /* INCLUDE_METALC_STDDEF_H_ */
