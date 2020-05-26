bits 64

%include "metalc/x86/metalc.inc"
%include "metalc/x86/setjmp.inc"

decl_mcapi setjmp
decl_mcapi longjmp


setjmp:
    fxsave  [FN_ARG_1_Q + tJmpBuf.j_fpu_state]
    mov     [FN_ARG_1_Q + tJmpBuf.j_bx], rbx
    mov     [FN_ARG_1_Q + tJmpBuf.j_si], rsi
    mov     [FN_ARG_1_Q + tJmpBuf.j_di], rdi
    mov     [FN_ARG_1_Q + tJmpBuf.j_sp], rsp
    mov     [FN_ARG_1_Q + tJmpBuf.j_bp], rbp
    mov     [FN_ARG_1_Q + tJmpBuf.j_r10], r10
    mov     [FN_ARG_1_Q + tJmpBuf.j_r11], r11
    mov     [FN_ARG_1_Q + tJmpBuf.j_r12], r12
    mov     [FN_ARG_1_Q + tJmpBuf.j_r13], r13
    mov     [FN_ARG_1_Q + tJmpBuf.j_r14], r14
    mov     [FN_ARG_1_Q + tJmpBuf.j_r15], r15

    %if USE_SHADOW_STACK
        %error "Using the shadow stack is not supported."
        rdsspq  rax
        mov     [FN_ARG_1_Q + tJmpBuf.j_shadow_stack_ptr], rax
    %endif

    ; Save return address. It's at the top of the stack, pointed to by rsp.
    mov     rax, [rsp]
    mov     [FN_ARG_1_Q + tJmpBuf.j_return], rax

    ; Always return 0.
    xor     rax, rax
    ret


longjmp:
    fxrstor [FN_ARG_1_Q + tJmpBuf.j_fpu_state]
    mov     rbx, [FN_ARG_1_Q + tJmpBuf.j_bx]
    mov     rsi, [FN_ARG_1_Q + tJmpBuf.j_si]
    mov     rdi, [FN_ARG_1_Q + tJmpBuf.j_di]
    mov     rsp, [FN_ARG_1_Q + tJmpBuf.j_sp]
    mov     rbp, [FN_ARG_1_Q + tJmpBuf.j_bp]
    mov     r10, [FN_ARG_1_Q + tJmpBuf.j_r10]
    mov     r11, [FN_ARG_1_Q + tJmpBuf.j_r11]
    mov     r12, [FN_ARG_1_Q + tJmpBuf.j_r12]
    mov     r13, [FN_ARG_1_Q + tJmpBuf.j_r13]
    mov     r14, [FN_ARG_1_Q + tJmpBuf.j_r14]
    mov     r15, [FN_ARG_1_Q + tJmpBuf.j_r15]

    %if USE_SHADOW_STACK
        %error "Using the shadow stack is not supported."
        rstorsspq   [FN_ARG_1_Q + tJmpBuf.j_shadow_stack_ptr]
    %endif

    ; Overwrite our return address to jump back into the function where we started.
    ; This will detonate if the shadow stack is enabled.
    mov     rax, [FN_ARG_1_Q + tJmpBuf.j_return]
    mov     [rsp], rax

    mov     rax, FN_ARG_2_Q
    ret
