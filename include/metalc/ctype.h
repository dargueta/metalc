#ifndef INCLUDE_METALC_CTYPE_H_
#define INCLUDE_METALC_CTYPE_H_

#include <metalc/metalc.h>

METALC_API_EXPORT int __mcapi_isalnum(int c);
METALC_API_EXPORT int __mcapi_isalpha(int c);
METALC_API_EXPORT int __mcapi_isblank(int c);
METALC_API_EXPORT int __mcapi_iscntrl(int c);
METALC_API_EXPORT int __mcapi_isdigit(int c);
METALC_API_EXPORT int __mcapi_isgraph(int c);
METALC_API_EXPORT int __mcapi_islower(int c);
METALC_API_EXPORT int __mcapi_isprint(int c);
METALC_API_EXPORT int __mcapi_ispunct(int c);
METALC_API_EXPORT int __mcapi_isspace(int c);
METALC_API_EXPORT int __mcapi_isupper(int c);
METALC_API_EXPORT int __mcapi_isxdigit(int c);
METALC_API_EXPORT int __mcapi_tolower(int c);
METALC_API_EXPORT int __mcapi_toupper(int c);

#endif  /* INCLUDE_METALC_CTYPE_H_ */
