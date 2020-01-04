%ifndef INCLUDE_METALC_SETJMP_INC_
%define INCLUDE_METALC_SETJMP_INC_

%include "metalc/x86/metalc.inc"

%if __BITS__ == 16
    %define reserve_register    resw 1
%elif __BITS__ == 32
    %define reserve_register    resd 1
%else
    %define reserve_register    resq 1
%endif

struc tJmpBuf
    .j_fpu_state:   resb 512        ; 0
    .j_shadow_stack_ptr:    resq 1  ; 512
    .j_bx:      reserve_register
    .j_si:      reserve_register
    .j_di:      reserve_register
    .j_sp:      reserve_register
    .j_bp:      reserve_register
    %if __BITS__ == 64
        .j_r10: resq 1
        .j_r11: resq 1
        .j_r12: resq 1
        .j_r13: resq 1
        .j_r14: resq 1
        .j_r15: resq 1
    %endif
    .j_return:  resq 1  ; Yes, use 64 bits regardless of platform
    .j_signal_mask  resq 1

    ; Pad to a multiple of 16
    %if __BITS__ == 16
        ._padding: resb 10
    %elif __BITS__ == 32
        ._padding: resb 10
    %else
        ._padding: resb 0
    %endif
endstruc
; Total size: 536 + 8 * REGISTER_SIZE (+64 if 64-bit architecture)
; 16-bit architecture: 536 + 12 = 538 -- round to 16 = 548
; 32-bit architecture: 536 + 24 = 554 -- round to 16 = 564
; 64-bit architecture: 536 + 96 = 624

%endif  ; INCLUDE_METALC_SETJMP_INC_
