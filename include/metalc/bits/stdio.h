#ifndef INCLUDE_METALC_BITS_STDIO_H_
#define INCLUDE_METALC_BITS_STDIO_H_

#include "../stddef.h"

#define mclib_BUFSIZ          8192    /* glibc uses this value so we might as well */
#define mclib_EOF             (-1)
#define mclib_FILENAME_MAX    256     /* Literally arbitrary */
#define mclib_FOPEN_MAX       16      /* Also arbitrary but glibc has this value */
#define mclib_L_tmpnam        32      /* Continue the arbitraryness */
#define mclib_SEEK_SET    0
#define mclib_SEEK_CUR    1
#define mclib_SEEK_END    2
#define mclib_IONBF 0
#define mclib_IOLBF 1
#define mclib_IOFBF 2

typedef ssize_t mclib_off_t;
typedef ssize_t mclib_fpos_t;

/* Only define the real values if we're not compiling for testing so that they
 * don't collide with the host OS's C library. */
#ifndef METALC_DISABLE_STDLIB_DEFS
    #define BUFSIZ          mclib_BUFSIZ
    #define EOF             mclib_EOF
    #define FILENAME_MAX    mclib_FILENAME_MAX
    #define FOPEN_MAX       mclib_FOPEN_MAX
    #define L_tmpnam        mclib_L_tmpnam
    #define SEEK_SET        mclib_SEEK_SET
    #define SEEK_CUR        mclib_SEEK_CUR
    #define SEEK_END        mclib_SEEK_END
    #define _IONBF          mclib_IONBF
    #define _IOLBF          mclib_IOLBF
    #define _IOFBF          mclib_IOFBF

    typedef mclib_off_t off_t;
    typedef mclib_fpos_t fpos_t;
#endif  /* METALC_DISABLE_STDLIB_DEFS */

#endif  /* INCLUDE_METALC_BITS_STDIO_H_ */
