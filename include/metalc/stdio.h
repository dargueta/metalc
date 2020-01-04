#ifndef INCLUDE_METALC_STDIO_H_
#define INCLUDE_METALC_STDIO_H_

#include <metalc/metalc.h>
#include <metalc/stdarg.h>
#include <metalc/stddef.h>


#define BUFSIZ  8192            /* glibc uses this value so we might as well */
#define EOF     -1
#define FILENAME_MAX    256     /* Literally arbitrary */
#define FOPEN_MAX       16      /* Also arbitrary; glibc has this value though */
#define L_tmpnam        32      /* Continue the arbitraryness */


struct FILE_;
typedef struct FILE_ FILE;
typedef ssize_t off_t;
typedef size_t fpos_t;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

METALC_API_EXPORT int vsprintf(char *buffer, const char *format, va_list arg_list);
METALC_API_EXPORT int sprintf(char *buffer, const char *format, ...);
METALC_API_EXPORT int vprintf(const char *format, va_list arg_list);
METALC_API_EXPORT int printf(const char *format, ...);

METALC_API_EXPORT int vfprintf(FILE *file, const char *format, va_list arg_list);
METALC_API_EXPORT int fprintf(FILE *file, const char *format, ...);

METALC_API_EXPORT void clearerr(FILE *stream);
METALC_API_EXPORT void fclose(FILE *stream);
METALC_API_EXPORT int feof(FILE *stream);
METALC_API_EXPORT int ferror(FILE *stream);
METALC_API_EXPORT FILE *fopen(const char *path, const char *mode);
METALC_API_EXPORT size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
METALC_API_EXPORT size_t fread(const void *ptr, size_t size, size_t count, FILE *stream);
METALC_API_EXPORT fpos_t fseek(FILE *file, long offset, int whence);

#endif  /* INCLUDE_METALC_STDIO_H_ */
