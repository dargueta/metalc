bits 32

%include "metalc/x86/metalc.inc"
%include "metalc/x86/setjmp.inc"

decl_mcint testhook_terminate
decl_mcint testhook_signal



testhook_terminate:
    mov     eax, 62     ; kill(2)
    mov     ecx, FN_ARG_1_D
    int     0x80
    ret


testhook_signal:
    mov     eax, 60     ; exit(2)
    mov     ecx, FN_ARG_1_D
    int     0x80
    ret
