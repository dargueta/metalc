#ifndef INCLUDE_METALC_SETJMP_H_
#define INCLUDE_METALC_SETJMP_H_

#include "metalc.h"


/** @cond INTERNAL_MACRO */
#if METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_X86_16
    #define BUFSIZE 548
#elif METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_X86_32
    #define BUFSIZE 564
#elif METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_X86_64
    #define BUFSIZE 624
#elif METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_MIPS32
    #define BUFSIZE 56
#elif METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_MIPS64
    #define BUFSIZE 112
#else
    #error "Unrecognized target architecture -- did you forget to update this list?"
#endif
/** @endcond */


typedef char mclib_jmp_buf[BUFSIZE] __attribute__((aligned (16)));

#undef BUFSIZE

METALC_EXPORT
GCC_ATTRIBUTE(returns_twice)
int setjmp(mclib_jmp_buf buf);

METALC_EXPORT
METALC_ATTR__NORETURN
int longjmp(mclib_jmp_buf buf, int code);


#ifndef METALC_DISABLE_STDLIB_DEFS
    typedef mclib_jmp_buf jmp_buf;
#endif


/** @cond DECL */
cstdlib_export(setjmp);
cstdlib_export(longjmp);
/** @endcond */

#endif  /* INCLUDE_METALC_SETJMP_H_ */
