#ifndef INCLUDE_METALC_CTYPE_H_
#define INCLUDE_METALC_CTYPE_H_

#include <metalc/metalc.h>

METALC_API_EXPORT int isalnum(int c);
METALC_API_EXPORT int isalpha(int c);
METALC_API_EXPORT int isblank(int c);
METALC_API_EXPORT int iscntrl(int c);
METALC_API_EXPORT int isdigit(int c);
METALC_API_EXPORT int isgraph(int c);
METALC_API_EXPORT int islower(int c);
METALC_API_EXPORT int isprint(int c);
METALC_API_EXPORT int ispunct(int c);
METALC_API_EXPORT int isspace(int c);
METALC_API_EXPORT int isupper(int c);
METALC_API_EXPORT int isxdigit(int c);
METALC_API_EXPORT int tolower(int c);
METALC_API_EXPORT int toupper(int c);

#endif  /* INCLUDE_METALC_CTYPE_H_ */
