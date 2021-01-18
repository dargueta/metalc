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


typedef char jmp_buf[BUFSIZE] __attribute__((aligned (16)));

#undef BUFSIZE


METALC_EXPORT_WITH_ATTR(returns_twice) int setjmp(jmp_buf buf);
METALC_EXPORT_WITH_ATTR(noreturn) int longjmp(jmp_buf buf, int code);

#endif  /* INCLUDE_METALC_SETJMP_H_ */
