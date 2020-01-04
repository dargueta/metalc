#ifndef INCLUDE_METALC_STDDEF_H_
#define INCLUDE_METALC_STDDEF_H_

#include <metalc/stdint.h>
#include <stddef.h>


/* Since we're compiling this library in strict ANSI C mode and POSIX specifies
 * some additional stuff, we can define it here without worrying that it'll
 * conflict with existing definitions. */

/* TODO (dargueta): This is pretty specific to GCC. */
#if __SIZEOF_SIZE_T__ == 8
    typedef int64_t ssize_t;
#elif __SIZEOF_SIZE_T__ == 4
    typedef int32_t ssize_t;
#elif __SIZEOF_SIZE_T__ == 2
    typedef int16_t ssize_t;
#else
    #error "Cannot define ssize_t: size_t width makes no sense: " ## __SIZEOF_SIZE_T__
#endif

#endif  /* INCLUDE_METALC_STDDEF_H_ */
