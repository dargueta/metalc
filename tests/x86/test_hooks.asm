%include "metalc/x86/metalc.inc"

%if ARCHITECTURE_SIZE == 16
    bits 16
%elif ARCHITECTURE_SIZE == 32
    bits 32
%else
    bits 64
%endif


decl_mint testhook_register_test
decl_mint testhook_begin_test
decl_mint testhook_end_test
decl_mint testhook_assertion_failed

testhook_log_message:
    ; Set RAX/EAX/AX to all bits on and halt. The testbench has a hook set for
    ; the HLT instruction that specifically waits for this.
    xor     REGISTER_AX, REGISTER_AX
    not     REGISTER_AX
    hlt
