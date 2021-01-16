bits 64

%include "metalc/x86/metalc.inc"
%include "metalc/x86/setjmp.inc"

decl_mcint testhook_terminate
decl_mcint testhook_signal



testhook_terminate:
    mov     rax, 62     ; kill(2)
    push    FN_ARG_1_Q
    int     0x80
    ret


testhook_signal:
    mov     rax, 60     ; exit(2)
    mov     rcx, FN_ARG_1_Q
    int     0x80
    ret
