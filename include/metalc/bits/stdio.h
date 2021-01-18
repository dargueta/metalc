#ifndef INCLUDE_METALC_BITS_STDIO_H_
#define INCLUDE_METALC_BITS_STDIO_H_

#include "../stddef.h"

#define BUFSIZ          8192    /* glibc uses this value so we might as well */
#define EOF             -1
#define FILENAME_MAX    256     /* Literally arbitrary */
#define FOPEN_MAX       16      /* Also arbitrary but glibc has this value */
#define L_tmpnam        32      /* Continue the arbitraryness */
#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

typedef ssize_t off_t;
typedef ssize_t fpos_t;

#endif  /* INCLUDE_METALC_BITS_STDIO_H_ */
