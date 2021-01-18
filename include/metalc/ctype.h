#ifndef INCLUDE_METALC_CTYPE_H_
#define INCLUDE_METALC_CTYPE_H_

#include "metalc.h"

METALC_API_EXPORT_WITH_ATTR(pure) int isalnum(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int isalpha(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int isblank(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int iscntrl(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isdigit(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int isgraph(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int islower(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int isprint(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int ispunct(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int isspace(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int isupper(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isxdigit(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int tolower(int c);
METALC_API_EXPORT_WITH_ATTR(pure) int toupper(int c);

#endif  /* INCLUDE_METALC_CTYPE_H_ */
