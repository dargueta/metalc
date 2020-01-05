#ifndef INCLUDE_METALC_STDIO_H_
#define INCLUDE_METALC_STDIO_H_

#include <metalc/metalc.h>
#include <metalc/stdarg.h>
#include <metalc/stddef.h>


#define __mcapi_BUFSIZ  8192            /* glibc uses this value so we might as well */
#define __mcapi_EOF     -1
#define __mcapi_FILENAME_MAX    256     /* Literally arbitrary */
#define __mcapi_FOPEN_MAX       16      /* Also arbitrary but glibc has this value */
#define __mcapi_L_tmpnam        32      /* Continue the arbitraryness */
#define __mcapi_SEEK_SET    0
#define __mcapi_SEEK_CUR    1
#define __mcapi_SEEK_END    2


struct __mcint_FILE;
typedef struct __mcint_FILE __mcapi_FILE;
typedef __mcapi_ssize_t __mcapi_off_t;
typedef __mcapi_ssize_t __mcapi_fpos_t;

extern __mcapi_FILE * const __mcapi_stdin;
extern __mcapi_FILE * const __mcapi_stdout;
extern __mcapi_FILE * const __mcapi_stderr;


METALC_API_EXPORT int __mcapi_vsprintf(char *buffer, const char *format, va_list arg_list);
METALC_API_EXPORT int __mcapi_sprintf(char *buffer, const char *format, ...);
METALC_API_EXPORT int __mcapi_vprintf(const char *format, va_list arg_list);
METALC_API_EXPORT int __mcapi_printf(const char *format, ...);
METALC_API_EXPORT int __mcapi_vfprintf(__mcapi_FILE *stream, const char *format, va_list arg_list);
METALC_API_EXPORT int __mcapi_fprintf(__mcapi_FILE *stream, const char *format, ...);

METALC_API_EXPORT void __mcapi_clearerr(__mcapi_FILE *stream);
METALC_API_EXPORT void __mcapi_fclose(__mcapi_FILE *stream);
METALC_API_EXPORT int __mcapi_feof(__mcapi_FILE *stream);
METALC_API_EXPORT int __mcapi_ferror(__mcapi_FILE *stream);
METALC_API_EXPORT __mcapi_FILE *__mcapi_fopen(const char *path, const char *mode);
METALC_API_EXPORT size_t __mcapi_fwrite(const void *ptr, size_t size, size_t count, __mcapi_FILE *stream);
METALC_API_EXPORT size_t __mcapi_fread(void *ptr, size_t size, size_t count, __mcapi_FILE *stream);
METALC_API_EXPORT __mcapi_fpos_t __mcapi_fseek(__mcapi_FILE *stream, long offset, int whence);

METALC_API_EXPORT int __mcint_mode_string_to_flags(const char *mode);

#endif  /* INCLUDE_METALC_STDIO_H_ */
