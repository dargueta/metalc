#ifndef INCLUDE_METALC_STDIO_H_
#define INCLUDE_METALC_STDIO_H_

#include "bits/stdio.h"
#include "metalc.h"
#include "stdarg.h"
#include "stddef.h"


struct __mcint_FILE;
typedef struct __mcint_FILE FILE;

extern FILE * const stdin;
extern FILE * const stdout;
extern FILE * const stderr;


METALC_EXPORT_WITH_ATTR(nonnull(2)) int vsprintf(char *buffer, const char *format, va_list arg_list);
METALC_EXPORT_WITH_ATTR(nonnull(3)) int vsnprintf(char *buffer, size_t size, const char *format, va_list arg_list);  /* Nonstandard */
METALC_EXPORT_WITH_ATTR(nonnull(3)) int snprintf(char *buffer, size_t length, const char *format, ...);
METALC_EXPORT_WITH_ATTR(nonnull(1, 2)) int sprintf(char *buffer, const char *format, ...);
METALC_EXPORT_WITH_ATTR(nonnull(1)) int vprintf(const char *format, va_list arg_list);
METALC_EXPORT_WITH_ATTR(nonnull(1)) int printf(const char *format, ...);
METALC_EXPORT_WITH_ATTR(nonnull(1, 2)) int vfprintf(FILE *stream, const char *format, va_list arg_list);
METALC_EXPORT_WITH_ATTR(nonnull(1, 2)) int fprintf(FILE *stream, const char *format, ...);
METALC_EXPORT_WITH_ATTR(nonnull) void clearerr(FILE *stream);
METALC_EXPORT_WITH_ATTR(nonnull) void fclose(FILE *stream);
METALC_EXPORT_WITH_ATTR(nonnull) int feof(FILE *stream);
METALC_EXPORT_WITH_ATTR(nonnull) int ferror(FILE *stream);
METALC_EXPORT_WITH_ATTR(nonnull, warn_unused_result) FILE *fopen(const char *path, const char *mode);
METALC_EXPORT_WITH_ATTR(nonnull) size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
METALC_EXPORT_WITH_ATTR(nonnull) size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
METALC_EXPORT_WITH_ATTR(nonnull) fpos_t fseek(FILE *stream, long offset, int whence);

int __mcint_mode_string_to_flags(const char *mode) __attribute__((nonnull));

#endif  /* INCLUDE_METALC_STDIO_H_ */
