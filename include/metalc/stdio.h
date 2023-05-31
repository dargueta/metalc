/**
 * Standard I/O utilities.
 *
 * @file stdio.h
 */

#ifndef INCLUDE_METALC_STDIO_H_
#define INCLUDE_METALC_STDIO_H_

#include "bits/stdio.h"
#include "metalc.h"
#include "stdarg.h"
#include "stddef.h"


struct mcinternal_FILE;
typedef struct mcinternal_FILE mclib_FILE;

extern mclib_FILE * const mclib_stdin;      /**< Standard input file handle */
extern mclib_FILE * const mclib_stdout;     /**< Standard output file handle */
extern mclib_FILE * const mclib_stderr;     /**< Standard error output file handle */


METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(2)
int vsprintf(char *buffer, const char *format, va_list arg_list);

METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(3)
int vsnprintf(char *buffer, size_t size, const char *format, va_list arg_list);

METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(1, 2)
int sprintf(char *buffer, const char *format, ...);

METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(1, 3)
int snprintf(char *buffer, size_t length, const char *format, ...);

METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(1)
int vprintf(const char *format, va_list arg_list);

METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(1)
int printf(const char *format, ...);


/**
 * Write formatted output to a file using a variadic argument list.
 *
 * The current implementation is inefficient in that it defers to @ref vsprintf
 * to write the entirety of the output to a buffer, then @ref fwrite s it to
 * @a stream. A more efficient way to do this would be to write directly into
 * @a stream without holding the entire result in memory.
 */
METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(1, 2)
int vfprintf(mclib_FILE *stream, const char *format, va_list arg_list);

METALC_EXPORT
METALC_ATTR__NONNULL_ARGS(1, 2)
int fprintf(mclib_FILE *stream, const char *format, ...);

METALC_EXPORT
METALC_ATTR__NONNULL
void clearerr(mclib_FILE *stream);

METALC_EXPORT
METALC_ATTR__NONNULL
void fclose(mclib_FILE *stream);

METALC_EXPORT
METALC_ATTR__NONNULL
int feof(mclib_FILE *stream);

METALC_EXPORT
METALC_ATTR__NONNULL
int ferror(mclib_FILE *stream);

METALC_EXPORT
METALC_ATTR__NONNULL
METALC_ATTR__NODISCARD
mclib_FILE *fopen(const char *path, const char *mode);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t fwrite(const void *ptr, size_t size, size_t count, mclib_FILE *stream);

METALC_EXPORT
METALC_ATTR__NONNULL
size_t fread(void *ptr, size_t size, size_t count, mclib_FILE *stream);

METALC_EXPORT
METALC_ATTR__NONNULL
mclib_fpos_t fseek(mclib_FILE *stream, long offset, int whence);

METALC_INTERNAL_ONLY
METALC_ATTR__NONNULL
int mcinternal_mode_string_to_flags(const char *mode);

#endif  /* INCLUDE_METALC_STDIO_H_ */
