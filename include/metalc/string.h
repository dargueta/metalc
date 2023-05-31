/**
 * @file string.h
 */

#ifndef INCLUDE_METALC_STRING_H_
#define INCLUDE_METALC_STRING_H_

#include "metalc.h"
#include "stddef.h"
#include "internal/string.h"


METALC_EXPORT
METALC_ATTR__NONNULL
void *memchr(const void *ptr, int value, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
int memcmp(const void *ptr1, const void *ptr2, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
void *memcpy(void *destination, const void *source, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
void *memmove(void *destination, const void *source, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
void *memset(void *ptr, int value, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strcat(char *destination, const char *source);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strchr(const char *str, int character);

METALC_EXPORT
METALC_ATTR__NONNULL
int strcmp(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
int strcoll(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strcpy(char *destination, const char *source);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t strcspn(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strerror(int errnum);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t strlen(const char *str);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strncat(char *destination, const char *source, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
int strncmp(const char *str1, const char *str2, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strncpy(char *destination, const char *source, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strpbrk(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strrchr(const char *str, int character);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t strspn(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strstr(const char *str, const char *substr);

METALC_EXPORT
METALC_ATTR__NONNULL
char *strtok(char *str, const char *delimiters);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t strxfrm(char *destination, const char *source, size_t num);


/** @cond DECL */
cstdlib_export(memchr);
cstdlib_export(memcmp);
cstdlib_export(memcpy);
cstdlib_export(memmove);
cstdlib_export(memset);
cstdlib_export(strcat);
cstdlib_export(strchr);
cstdlib_export(strcmp);
cstdlib_export(strcoll);
cstdlib_export(strcpy);
cstdlib_export(strcspn);
cstdlib_export(strerror);
cstdlib_export(strlen);
cstdlib_export(strncat);
cstdlib_export(strncmp);
cstdlib_export(strncpy);
cstdlib_export(strpbrk);
cstdlib_export(strrchr);
cstdlib_export(strspn);
cstdlib_export(strstr);
cstdlib_export(strtok);
cstdlib_export(strxfrm);
/** @endcond */


#endif  /* INCLUDE_METALC_STRING_H_ */
