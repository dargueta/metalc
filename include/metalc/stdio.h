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


int vsprintf(char *buffer, const char *format, va_list arg_list);
int vsnprintf(char *buffer, size_t size, const char *format, va_list arg_list);
int snprintf(char *buffer, size_t length, const char *format, ...);
int sprintf(char *buffer, const char *format, ...);
int vprintf(const char *format, va_list arg_list);
int printf(const char *format, ...);

/**
 * Write formatted output to a file using a variadic argument list.
 *
 * The current implementation is inefficient in that it defers to @ref vsprintf
 * to write the entirety of the output to a buffer, then @ref fwrite s it to
 * @a stream. A more efficient way to do this would be to write directly into
 * @a stream without holding the entire result in memory.
 */
int vfprintf(mclib_FILE *stream, const char *format, va_list arg_list);
int fprintf(mclib_FILE *stream, const char *format, ...);
void clearerr(mclib_FILE *stream);
void fclose(mclib_FILE *stream);
int feof(mclib_FILE *stream);
int ferror(mclib_FILE *stream);
mclib_FILE *fopen(const char *path, const char *mode);
size_t fwrite(const void *ptr, size_t size, size_t count, mclib_FILE *stream);
size_t fread(void *ptr, size_t size, size_t count, mclib_FILE *stream);
mclib_fpos_t fseek(mclib_FILE *stream, long offset, int whence);

METALC_INTERNAL_ONLY_WITH_ATTR(nonnull)
int mcinternal_mode_string_to_flags(const char *mode);


cstdlib_export_with_attr(vsprintf, nonnull(2));
cstdlib_export_with_attr(vsnprintf, nonnull(3));
cstdlib_export_with_attr(sprintf, nonnull(1, 2));
cstdlib_export_with_attr(snprintf, nonnull(1, 3));
cstdlib_export_with_attr(vprintf, nonnull(1));
cstdlib_export_with_attr(printf, nonnull(1));
cstdlib_export_with_attr(vfprintf, nonnull(1, 2));
cstdlib_export_with_attr(fprintf, nonnull(1, 2));
cstdlib_export_with_attr(clearerr, nonnull);
cstdlib_export_with_attr(fclose, nonnull);
cstdlib_export_with_attr(feof, nonnull);
cstdlib_export_with_attr(ferror, nonnull);
cstdlib_export_with_attr(fopen, nonnull, warn_unused_result);
cstdlib_export_with_attr(fwrite, nonnull);
cstdlib_export_with_attr(fread, nonnull);
cstdlib_export_with_attr(fseek, nonnull);

#endif  /* INCLUDE_METALC_STDIO_H_ */
