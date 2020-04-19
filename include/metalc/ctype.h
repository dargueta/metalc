#ifndef INCLUDE_METALC_CTYPE_H_
#define INCLUDE_METALC_CTYPE_H_

#include <metalc/metalc.h>

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

cstdlib_export_with_attr(isalnum, pure);
cstdlib_export_with_attr(isalpha, pure);
cstdlib_export_with_attr(isblank, pure);
cstdlib_export_with_attr(iscntrl, pure);
cstdlib_export_with_attr(isdigit, const);
cstdlib_export_with_attr(isgraph, pure);
cstdlib_export_with_attr(islower, pure);
cstdlib_export_with_attr(isprint, pure);
cstdlib_export_with_attr(ispunct, pure);
cstdlib_export_with_attr(isspace, pure);
cstdlib_export_with_attr(isupper, pure);
cstdlib_export_with_attr(isxdigit, const);
cstdlib_export_with_attr(tolower, pure);
cstdlib_export_with_attr(toupper, pure);

#endif  /* INCLUDE_METALC_CTYPE_H_ */
