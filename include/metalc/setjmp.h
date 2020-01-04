#ifndef INCLUDE_METALC_SETJMP_H_
#define INCLUDE_METALC_SETJMP_H_

#include <metalc/metalc.h>

#if METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_X86_16
    typedef char jmp_buf[548];
#elif METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_X86_32
    typedef char jmp_buf[564];
#elif METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_X86_64
    typedef char jmp_buf[624];
#elif METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_MIPS32
    typedef char jmp_buf[56];
#elif METALC_TARGET_ARCHITECTURE_ID == METALC_TARGET_ARCHITECTURE_MIPS64
    typedef char jmp_buf[112];
#else
    #error "Unrecognized target architecture -- did you forget to change this?"
#endif

METALC_API_EXPORT_FAST int setjmp(jmp_buf buf);
METALC_API_EXPORT_FAST_WITH_ATTR(noreturn) int longjmp(jmp_buf buf, int code);

#endif  /* INCLUDE_METALC_SETJMP_H_ */
