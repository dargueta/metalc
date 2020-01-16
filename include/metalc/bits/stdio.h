#ifndef INCLUDE_METALC_BITS_STDIO_H_
#define INCLUDE_METALC_BITS_STDIO_H_

#include <metalc/stddef.h>

#define __mcapi_BUFSIZ          8192    /* glibc uses this value so we might as well */
#define __mcapi_EOF             -1
#define __mcapi_FILENAME_MAX    256     /* Literally arbitrary */
#define __mcapi_FOPEN_MAX       16      /* Also arbitrary but glibc has this value */
#define __mcapi_L_tmpnam        32      /* Continue the arbitraryness */
#define __mcapi_SEEK_SET    0
#define __mcapi_SEEK_CUR    1
#define __mcapi_SEEK_END    2

typedef ssize_t __mcapi_off_t;
typedef ssize_t __mcapi_fpos_t;

/* Only define the real values if we're not compiling for testing so that they
 * don't collide with the host OS's C library. */
#if !defined METALC_DISABLE_STDLIB_DEFS
    #define BUFSIZ          __mcapi_BUFSIZ
    #define EOF             __mcapi_EOF
    #define FILENAME_MAX    __mcapi_FILENAME_MAX
    #define FOPEN_MAX       __mcapi_FOPEN_MAX
    #define L_tmpnam        __mcapi_L_tmpnam
    #define SEEK_SET        __mcapi_SEEK_SET
    #define SEEK_CUR        __mcapi_SEEK_CUR
    #define SEEK_END        __mcapi_SEEK_END

    typedef __mcapi_off_t off_t;
    typedef __mcapi_fpos_t fpos_t;
#endif  /* METALC_DISABLE_STDLIB_DEFS */

#endif  /* INCLUDE_METALC_BITS_STDIO_H_ */
