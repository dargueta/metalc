/**
 * @file string.h
 */

#ifndef INCLUDE_METALC_STRING_H_
#define INCLUDE_METALC_STRING_H_

#include <metalc/metalc.h>
#include <metalc/stddef.h>


METALC_API_EXPORT void *memchr(const void *ptr, int value, size_t num);
METALC_API_EXPORT int memcmp(const void *ptr1, const void *ptr2, size_t num);
METALC_API_EXPORT void *memcpy(void *destination, const void *source, size_t num);
METALC_API_EXPORT void *memmove(void *destination, const void *source, size_t num);
METALC_API_EXPORT void *memset(void *ptr, int value, size_t num);
METALC_API_EXPORT char *strcat(char *destination, const char *source);
METALC_API_EXPORT char *strchr(const char *str, int character);
METALC_API_EXPORT int strcmp(const char *str1, const char *str2);

/**
 * @warn Standards violation: Identical to @ref strcmp.
 */
METALC_API_EXPORT int strcoll(const char *str1, const char *str2);
METALC_API_EXPORT char *strcpy(char *destination, const char *source);
METALC_API_EXPORT size_t strcspn(const char *str1, const char *str2);
METALC_API_EXPORT char *strerror(int errnum);
METALC_API_EXPORT size_t strlen(const char *str);
METALC_API_EXPORT char *strncat(char *destination, const char *source, size_t num);
METALC_API_EXPORT int strncmp(const char *str1, const char *str2, size_t num);
METALC_API_EXPORT char *strncpy(char *destination, const char *source, size_t num);
METALC_API_EXPORT char *strpbrk(const char *str1, const char *str2);
METALC_API_EXPORT char *strrchr(const char *str, int character);
METALC_API_EXPORT size_t strspn(const char *str1, const char *str2);
METALC_API_EXPORT char *strstr(const char *str, const char *substr);
METALC_API_EXPORT char *strtok(char *str, const char *delimiters);


/**
 * @warn Standards violation: Performs no transform, nearly identical to @ref strncpy.
 */
METALC_API_EXPORT size_t strxfrm(char *destination, const char *source, size_t num);


#endif  /* INCLUDE_METALC_STRING_H_ */
