#ifndef INCLUDE_METALC_CTYPE_H_
#define INCLUDE_METALC_CTYPE_H_

#include "metalc.h"

METALC_API_EXPORT_WITH_ATTR(const) int isalnum(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isalpha(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isblank(int c);
METALC_API_EXPORT_WITH_ATTR(const) int iscntrl(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isdigit(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isgraph(int c);
METALC_API_EXPORT_WITH_ATTR(const) int islower(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isprint(int c);
METALC_API_EXPORT_WITH_ATTR(const) int ispunct(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isspace(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isupper(int c);
METALC_API_EXPORT_WITH_ATTR(const) int isxdigit(int c);
METALC_API_EXPORT_WITH_ATTR(const) int tolower(int c);
METALC_API_EXPORT_WITH_ATTR(const) int toupper(int c);

#endif  /* INCLUDE_METALC_CTYPE_H_ */
