#ifndef INCLUDE_METALC_STDDEF_H_
#define INCLUDE_METALC_STDDEF_H_

#include "metalc.h"
#include "stdint.h"


typedef uintptr_t size_t;
typedef intptr_t ssize_t;

#define SIZE_MAX UINTPTR_MAX
#define SSIZE_MIN INTPTR_MIN
#define SSIZE_MAX INTPTR_MAX

/* TODO (dargueta): Is this correct? */
typedef intmax_t max_align_t;

#ifndef offsetof
#   define offsetof(type, member)  ((size_t)(&(((type *)0)->(member))))
#endif


typedef uint_least32_t wchar_t;

#define WCHAR_MIN   0
#define WCHAR_MAX   UINT_LEAST32_MAX

#ifndef NULL
#   define NULL    ((void *)0)
#endif

#endif  /* INCLUDE_METALC_STDDEF_H_ */
