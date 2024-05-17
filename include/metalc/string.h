/**
 * @file string.h
 */

#ifndef INCLUDE_METALC_STRING_H_
#define INCLUDE_METALC_STRING_H_

#include "metalc.h"
#include "stddef.h"
#include "internal/poison.h"
#include "internal/string.h"


METALC_EXPORT
METALC_ATTR__NONNULL
void *LIBC_GUARD(memchr)(const void *ptr, int value, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
int LIBC_GUARD(memcmp)(const void *ptr1, const void *ptr2, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
void *LIBC_GUARD(memcpy)(void *destination, const void *source, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
void *LIBC_GUARD(memmove)(void *destination, const void *source, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
void *LIBC_GUARD(memset)(void *ptr, int value, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strcat)(char *destination, const char *source);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strchr)(const char *str, int character);

METALC_EXPORT
METALC_ATTR__NONNULL
int LIBC_GUARD(strcmp)(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
int LIBC_GUARD(strcoll)(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strcpy)(char *destination, const char *source);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t LIBC_GUARD(strcspn)(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strerror)(int errnum);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t LIBC_GUARD(strlen)(const char *str);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strncat)(char *destination, const char *source, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
int LIBC_GUARD(strncmp)(const char *str1, const char *str2, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strncpy)(char *destination, const char *source, size_t num);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strpbrk)(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strrchr)(const char *str, int character);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t LIBC_GUARD(strspn)(const char *str1, const char *str2);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strstr)(const char *str, const char *substr);

METALC_EXPORT
METALC_ATTR__NONNULL
char *LIBC_GUARD(strtok)(char *str, const char *delimiters);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t LIBC_GUARD(strxfrm)(char *destination, const char *source, size_t num);


/** @cond DECL */
DECLARE_LIBC(memchr)
DECLARE_LIBC(memcmp)
DECLARE_LIBC(memcpy)
DECLARE_LIBC(memmove)
DECLARE_LIBC(memset)
DECLARE_LIBC(strcat)
DECLARE_LIBC(strchr)
DECLARE_LIBC(strcmp)
DECLARE_LIBC(strcoll)
DECLARE_LIBC(strcpy)
DECLARE_LIBC(strcspn)
DECLARE_LIBC(strerror)
DECLARE_LIBC(strlen)
DECLARE_LIBC(strncat)
DECLARE_LIBC(strncmp)
DECLARE_LIBC(strncpy)
DECLARE_LIBC(strpbrk)
DECLARE_LIBC(strrchr)
DECLARE_LIBC(strspn)
DECLARE_LIBC(strstr)
DECLARE_LIBC(strtok)
DECLARE_LIBC(strxfrm)
/** @endcond */


#endif  /* INCLUDE_METALC_STRING_H_ */
