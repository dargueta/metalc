/**
 * @file string.h
 */

#ifndef INCLUDE_METALC_STRING_H_
#define INCLUDE_METALC_STRING_H_

#include <metalc/metalc.h>
#include <metalc/stddef.h>


METALC_API_EXPORT void *__mcapi_memchr(const void *ptr, int value, size_t num);
METALC_API_EXPORT int __mcapi_memcmp(const void *ptr1, const void *ptr2, size_t num);
METALC_API_EXPORT void *__mcapi_memcpy(void *destination, const void *source, size_t num);
METALC_API_EXPORT void *__mcapi_memmove(void *destination, const void *source, size_t num);
METALC_API_EXPORT void *__mcapi_memset(void *ptr, int value, size_t num);
METALC_API_EXPORT char *__mcapi_strcat(char *destination, const char *source);
METALC_API_EXPORT char *__mcapi_strchr(const char *str, int character);
METALC_API_EXPORT int __mcapi_strcmp(const char *str1, const char *str2);

/**
 * @warn Standards violation: Identical to @ref strcmp.
 */
METALC_API_EXPORT int __mcapi_strcoll(const char *str1, const char *str2);
METALC_API_EXPORT char *__mcapi_strcpy(char *destination, const char *source);
METALC_API_EXPORT size_t __mcapi_strcspn(const char *str1, const char *str2);
METALC_API_EXPORT char *__mcapi_strerror(int errnum);
METALC_API_EXPORT size_t __mcapi_strlen(const char *str);
METALC_API_EXPORT char *__mcapi_strncat(char *destination, const char *source, size_t num);
METALC_API_EXPORT int __mcapi_strncmp(const char *str1, const char *str2, size_t num);
METALC_API_EXPORT char *__mcapi_strncpy(char *destination, const char *source, size_t num);
METALC_API_EXPORT char *__mcapi_strpbrk(const char *str1, const char *str2);
METALC_API_EXPORT char *__mcapi_strrchr(const char *str, int character);
METALC_API_EXPORT size_t __mcapi_strspn(const char *str1, const char *str2);
METALC_API_EXPORT char *__mcapi_strstr(const char *str, const char *substr);
METALC_API_EXPORT char *__mcapi_strtok(char *str, const char *delimiters);


/**
 * @warn Standards violation: Performs no transform, nearly identical to @ref strncpy.
 */
METALC_API_EXPORT size_t __mcapi_strxfrm(char *destination, const char *source, size_t num);


#endif  /* INCLUDE_METALC_STRING_H_ */
