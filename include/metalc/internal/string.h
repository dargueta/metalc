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
#include "../stddef.h"


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
METALC_API_INTERAL_WITH_ATTR(nonnull)
size_t strcpy_and_update_buffer(const char *source, void **buffer);

#endif
