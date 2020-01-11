#ifndef INCLUDE_METALC_SETJMP_H_
#define INCLUDE_METALC_SETJMP_H_

#include <metalc/metalc.h>


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


typedef char __mcapi_jmp_buf[BUFSIZE] __attribute__((aligned (16)));

#undef BUFSIZE

METALC_API_EXPORT_FAST int __mcapi_setjmp(__mcapi_jmp_buf buf);
METALC_API_EXPORT_FAST_WITH_ATTR(noreturn) int __mcapi_longjmp(__mcapi_jmp_buf buf, int code);

#endif  /* INCLUDE_METALC_SETJMP_H_ */
