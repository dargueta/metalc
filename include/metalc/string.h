/**
 * @file string.h
 */

#ifndef INCLUDE_METALC_STRING_H_
#define INCLUDE_METALC_STRING_H_

#include "metalc.h"
#include "stddef.h"
#include "internal/string.h"


void *memchr(const void *ptr, int value, size_t num);
int memcmp(const void *ptr1, const void *ptr2, size_t num);
void *memcpy(void *destination, const void *source, size_t num);
void *memmove(void *destination, const void *source, size_t num);
void *memset(void *ptr, int value, size_t num);
char *strcat(char *destination, const char *source);
char *strchr(const char *str, int character);
int strcmp(const char *str1, const char *str2);
int strcoll(const char *str1, const char *str2);
char *strcpy(char *destination, const char *source);
size_t strcspn(const char *str1, const char *str2);
char *strerror(int errnum);
size_t strlen(const char *str);
char *strncat(char *destination, const char *source, size_t num);
int strncmp(const char *str1, const char *str2, size_t num);
char *strncpy(char *destination, const char *source, size_t num);
char *strpbrk(const char *str1, const char *str2);
char *strrchr(const char *str, int character);
size_t strspn(const char *str1, const char *str2);
char *strstr(const char *str, const char *substr);
char *strtok(char *str, const char *delimiters);
/**
 * @warning Standards violation: Performs no transform, nearly identical to @ref strncpy.
 */
size_t strxfrm(char *destination, const char *source, size_t num);


/** @cond DECL */
cstdlib_export_with_attr(memchr, nonnull);
cstdlib_export_with_attr(memcmp, nonnull, pure);
cstdlib_export_with_attr(memcpy, nonnull);
cstdlib_export_with_attr(memmove, nonnull);
cstdlib_export_with_attr(memset, nonnull);
cstdlib_export_with_attr(strcat, nonnull);
cstdlib_export_with_attr(strchr, nonnull);
cstdlib_export_with_attr(strcmp, nonnull);
cstdlib_export_with_attr(strcoll, nonnull);
cstdlib_export_with_attr(strcpy, nonnull);
cstdlib_export_with_attr(strcspn, nonnull);
cstdlib_export(strerror);
cstdlib_export_with_attr(strlen, nonnull, pure);
cstdlib_export_with_attr(strncat, nonnull);
cstdlib_export_with_attr(strncmp, nonnull);
cstdlib_export_with_attr(strncpy, nonnull);
cstdlib_export_with_attr(strpbrk, nonnull);
cstdlib_export_with_attr(strrchr, nonnull);
cstdlib_export_with_attr(strspn, nonnull);
cstdlib_export_with_attr(strstr, nonnull);
cstdlib_export_with_attr(strtok, nonnull(2));
cstdlib_export_with_attr(strxfrm, nonnull(2));
/** @endcond */


#endif  /* INCLUDE_METALC_STRING_H_ */
