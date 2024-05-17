/**
 * Declarations of string functions for internal use only.
 *
 * These functions aren't exported in the linked library and there's no way to
 * include this file using the standard library headers. Only .c files should be
 * including this file.
 *
 * @file string.h
 */

#ifndef INCLUDE_MCINTERNAL_STRING_H_
#define INCLUDE_MCINTERNAL_STRING_H_

#include "../metalc.h"
#include <stddef.h>

/**
 * Copy the string pointed to by `source` into the pointer `*buffer`, and update
 * `*buffer` to point to the terminating null just written.
 *
 * @param source    The source string to copy.
 * @param buffer    A pointer to a pointer that points to the location where the
 *                  string is to be copied. After the copy, *buffer will be
 *                  updated to point to the terminating null just written into
 *                  memory.
 *
 * @return The number of bytes copied, not including the terminating null.
 */
METALC_INTERNAL_ONLY
METALC_ATTR__NONNULL
size_t strcpy_and_update_buffer(const char *source, char **buffer);

/**
 * Same as @ref strcpy_and_update_buffer except copies at most @a n chars.
 */
METALC_INTERNAL_ONLY
METALC_ATTR__NONNULL
size_t strncpy_and_update_buffer(const char *source, char **buffer, size_t n);

typedef int (*fptr_strcoll)(const char *str1, const char *str2);
typedef size_t (*fptr_strxfrm)(char *destination, const char *source, size_t num);

struct mcinternal_collation_info
{
    /* The name of this collation order. */
    const char *const name;

    /** A pointer to the function implementing @ref strcoll for the selected collation. */
    fptr_strcoll f_strcoll;

    /** A pointer to the function implementing @ref strxfrm for the selected collation. */
    fptr_strxfrm f_strxfrm;
};

METALC_INTERNAL_ONLY
extern const struct mcinternal_collation_info *mcinternal_ptr_current_coll;

#endif
