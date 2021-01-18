/**
 * @file string.h
 */

#ifndef INCLUDE_METALC_STRING_H_
#define INCLUDE_METALC_STRING_H_

#include "metalc.h"
#include "stddef.h"
#include "internal/string.h"


METALC_API_EXPORT_WITH_ATTR(nonnull) void *memchr(const void *ptr, int value, size_t num);
METALC_API_EXPORT_WITH_ATTR(nonnull, pure) int memcmp(const void *ptr1, const void *ptr2, size_t num);
METALC_API_EXPORT_WITH_ATTR(nonnull) void *memcpy(void *destination, const void *source, size_t num);
METALC_API_EXPORT_WITH_ATTR(nonnull) void *memmove(void *destination, const void *source, size_t num);
METALC_API_EXPORT_WITH_ATTR(nonnull) void *memset(void *ptr, int value, size_t num);
METALC_API_EXPORT_WITH_ATTR(nonnull) char *strcat(char *destination, const char *source);
METALC_API_EXPORT_WITH_ATTR(nonnull) char *strchr(const char *str, int character);
METALC_API_EXPORT_WITH_ATTR(nonnull) int strcmp(const char *str1, const char *str2);

/**
 * @warning Standards violation: Identical to @ref strcmp.
 */
METALC_API_EXPORT_WITH_ATTR(nonnull) int strcoll(const char *str1, const char *str2);
METALC_API_EXPORT_WITH_ATTR(nonnull) char *strcpy(char *destination, const char *source);
METALC_API_EXPORT_WITH_ATTR(nonnull) size_t strcspn(const char *str1, const char *str2);
METALC_API_EXPORT char *strerror(int errnum);
METALC_API_EXPORT_WITH_ATTR(nonnull, pure) size_t strlen(const char *str);
METALC_API_EXPORT_WITH_ATTR(nonnull) char *strncat(char *destination, const char *source, size_t num);
METALC_API_EXPORT_WITH_ATTR(nonnull) int strncmp(const char *str1, const char *str2, size_t num);
METALC_API_EXPORT_WITH_ATTR(nonnull) char *strncpy(char *destination, const char *source, size_t num);
METALC_API_EXPORT_WITH_ATTR(nonnull) char *strpbrk(const char *str1, const char *str2);
METALC_API_EXPORT_WITH_ATTR(nonnull) char *strrchr(const char *str, int character);
METALC_API_EXPORT_WITH_ATTR(nonnull) size_t strspn(const char *str1, const char *str2);
METALC_API_EXPORT_WITH_ATTR(nonnull) char *strstr(const char *str, const char *substr);
METALC_API_EXPORT_WITH_ATTR(nonnull(2)) char *strtok(char *str, const char *delimiters);


/**
 * @warning Standards violation: Performs no transform, nearly identical to @ref strncpy.
 */
METALC_API_EXPORT_WITH_ATTR(nonnull(2)) size_t strxfrm(char *destination, const char *source, size_t num);


#endif  /* INCLUDE_METALC_STRING_H_ */
