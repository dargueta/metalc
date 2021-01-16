bits 16

%include "metalc/x86/metalc.inc"
%include "metalc/x86/setjmp.inc"

decl_mcint testhook_terminate
decl_mcint testhook_signal



testhook_terminate:
    mov     ax, 62  ; kill(2)
    mov     cx, FN_ARG_1_W
    int     0x80
    ret


testhook_signal:
    mov     ax, 60  ; exit(2)
    mov     cx, FN_ARG_1_W
    int     0x80
    ret
