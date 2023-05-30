#ifndef INCLUDE_METALC_CTYPE_H_
#define INCLUDE_METALC_CTYPE_H_

#include "metalc.h"

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int isalnum(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int isalpha(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int isblank(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int iscntrl(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int isdigit(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int isgraph(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int islower(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int isprint(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int ispunct(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int isspace(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int isupper(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int isxdigit(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNC
int tolower(int c);

METALC_EXPORT
METALC_ATTR__CONST_FUNCint toupper(int c);

cstdlib_export(isalnum);
cstdlib_export(isalpha);
cstdlib_export(isblank);
cstdlib_export(iscntrl);
cstdlib_export(isdigit);
cstdlib_export(isgraph);
cstdlib_export(islower);
cstdlib_export(isprint);
cstdlib_export(ispunct);
cstdlib_export(isspace);
cstdlib_export(isupper);
cstdlib_export(isxdigit);
cstdlib_export(tolower);
cstdlib_export(toupper);

#endif  /* INCLUDE_METALC_CTYPE_H_ */
