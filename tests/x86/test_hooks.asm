%include "metalc/x86/metalc.inc"

%if ARCHITECTURE_SIZE == 16
    bits 16
%elif ARCHITECTURE_SIZE == 32
    bits 32
%else
    bits 64
%endif


decl_mint testhook_log_message

testhook_log_message:
    ; Set RAX/EAX/AX to all bits on and call interrupt 0x80. The testbench will
    ; detect this call and intercept it but otherwise let other calls through
    ; to the original handler.
    xor     REGISTER_AX, REGISTER_AX
    not     REGISTER_AX
    int     0x80
