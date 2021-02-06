%include "metalc/x86/metalc.inc"


%if ARCHITECTURE_SIZE == 16
    bits 16
%elif ARCHITECTURE_SIZE == 32
    bits 32
%else
    bits 64
%endif


decl_mcint testhook_log_message

testhook_log_message:
    xor     REGISTER_AX, REGISTER_AX
    not     REGISTER_AX
    int     0x80
