bits 32

%include "metalc/x86/metalc.inc"
%include "metalc/x86/setjmp.inc"

global mclib_setjmp:function
global mclib_longjmp:function


mclib_setjmp:
    fxsave  [FN_ARG_1_D + tJmpBuf.j_fpu_state]
    mov     [FN_ARG_1_D + tJmpBuf.j_ebx], ebx
    mov     [FN_ARG_1_D + tJmpBuf.j_esi], esi
    mov     [FN_ARG_1_D + tJmpBuf.j_edi], edi
    mov     [FN_ARG_1_D + tJmpBuf.j_esp], esp
    mov     [FN_ARG_1_D + tJmpBuf.j_ebp], ebp

    %if USE_SHADOW_STACK
        rdsspd  eax
        mov     [FN_ARG_1_D + tJmpBuf.j_shadow_stack_ptr], eax
    %endif

    ; Save return address. It's at the top of the stack, pointed to by rsp.
    mov     eax, [esp]
    mov     [FN_ARG_1_D + tJmpBuf.j_rflags], eax

    ; Always return 0.
    xor     eax, eax
    ret


mclib_longjmp:
    fxrstor     [FN_ARG_1_D + tJmpBuf.j_fpu_state]

    %if USE_SHADOW_STACK
        %error "Using the shadow stack is not supported."
    ;     rstorsspd   [FN_ARG_1_D + tJmpBuf.j_shadow_stack_ptr]
    %endif

    ; Overwrite our return address to jump back into the function where we started.
    ; This will detonate if the shadow stack is enabled.
    mov     eax, [FN_ARG_1_D + tJmpBuf.j_return]
    mov     [esp], eax

    mov     ebx, [FN_ARG_1_D + tJmpBuf.j_bx]
    mov     esi, [FN_ARG_1_D + tJmpBuf.j_si]
    mov     edi, [FN_ARG_1_D + tJmpBuf.j_di]
    mov     esp, [FN_ARG_1_D + tJmpBuf.j_sp]
    mov     ebp, [FN_ARG_1_D + tJmpBuf.j_bp]
    mov     eax, FN_ARG_2_D
    ret
