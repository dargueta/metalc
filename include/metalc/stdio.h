#ifndef INCLUDE_METALC_STDIO_H_
#define INCLUDE_METALC_STDIO_H_

#include "bits/stdio.h"
#include "metalc.h"
#include "stdarg.h"
#include "stddef.h"


struct __mcint_FILE;
typedef struct __mcint_FILE __mcapi_FILE;

extern __mcapi_FILE * const __mcapi_stdin;
extern __mcapi_FILE * const __mcapi_stdout;
extern __mcapi_FILE * const __mcapi_stderr;


int vsprintf(char *buffer, const char *format, va_list arg_list);
int vsnprintf(char *buffer, size_t size, const char *format, va_list arg_list);
int snprintf(char *buffer, size_t length, const char *format, ...);
int sprintf(char *buffer, const char *format, ...);
int vprintf(const char *format, va_list arg_list);
int printf(const char *format, ...);
int vfprintf(__mcapi_FILE *stream, const char *format, va_list arg_list);
int fprintf(__mcapi_FILE *stream, const char *format, ...);
void clearerr(__mcapi_FILE *stream);
void fclose(__mcapi_FILE *stream);
int feof(__mcapi_FILE *stream);
int ferror(__mcapi_FILE *stream);
__mcapi_FILE *fopen(const char *path, const char *mode);
size_t fwrite(const void *ptr, size_t size, size_t count, __mcapi_FILE *stream);
size_t fread(void *ptr, size_t size, size_t count, __mcapi_FILE *stream);
__mcapi_fpos_t fseek(__mcapi_FILE *stream, long offset, int whence);

int __mcint_mode_string_to_flags(const char *mode) __attribute__((nonnull));


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
