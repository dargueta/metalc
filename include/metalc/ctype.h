#ifndef INCLUDE_METALC_CTYPE_H_
#define INCLUDE_METALC_CTYPE_H_

#include "metalc.h"

int isalnum(int c);
int isalpha(int c);
int isblank(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int tolower(int c);
int toupper(int c);

cstdlib_export_with_attr(isalnum, const);
cstdlib_export_with_attr(isalpha, const);
cstdlib_export_with_attr(isblank, const);
cstdlib_export_with_attr(iscntrl, const);
cstdlib_export_with_attr(isdigit, const);
cstdlib_export_with_attr(isgraph, const);
cstdlib_export_with_attr(islower, const);
cstdlib_export_with_attr(isprint, const);
cstdlib_export_with_attr(ispunct, const);
cstdlib_export_with_attr(isspace, const);
cstdlib_export_with_attr(isupper, const);
cstdlib_export_with_attr(isxdigit, const);
cstdlib_export_with_attr(tolower, const);
cstdlib_export_with_attr(toupper, const);

#endif  /* INCLUDE_METALC_CTYPE_H_ */
