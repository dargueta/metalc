%ifndef INCLUDE_METALC_X86_METALC_INC_
%define INCLUDE_METALC_X86_METALC_INC_

%define ABI_MICROSOFT           @METALC_ABI_MICROSOFT@
%define ABI_GNU                 @METALC_ABI_GNU@
%define INTERNALS_USE_FASTCALL  @METALC_INTERNALS_USE_FASTCALL@
%define COMPILE_FOR_KERNEL      @METALC_COMPILE_FOR_KERNEL@
%define USE_SHADOW_STACK        @METALC_COMPILE_OPTION_X86_USE_SHADOW_STACK@
%define COMPILE_FOR_TESTING     @METALC_COMPILE_FOR_TESTING@

%if !(ABI_MICROSOFT || ABI_GNU)
    %error "No calling convention specified."
%endif


%if COMPILE_FOR_TESTING
    ; Building the C library for use by the testbench code
    %macro decl_mcint 1
        global %1:function hidden
        global mcinternal_%1:function
    %endmacro

    %macro decl_mcapi 1
        global %1:function hidden
        global mclib_%1:function
    %endmacro
%else
    ; Building for production
    %macro decl_mcint 1
        global %1:function
    %endmacro

    %macro decl_mcapi 1
        global %1:function
    %endmacro
%endif


%if __BITS__ == 64
    %define REGISTER_AX     rax
    %define REGISTER_BX     rbx
    %define REGISTER_CX     rcx
    %define REGISTER_DX     rdx

    %if ABI_MICROSOFT
        %define FN_ARG_1_B  cl
        %define FN_ARG_2_B  dl
        %define FN_ARG_3_B  r8b
        %define FN_ARG_4_B  r9b
        %define FN_ARG_5_B  BYTE [rbp + 16]
        %define FN_ARG_6_B  BYTE [rbp + 24]

        %define FN_ARG_1_W  cx
        %define FN_ARG_2_W  dx
        %define FN_ARG_3_W  r8w
        %define FN_ARG_4_W  r9w
        %define FN_ARG_5_W  WORD [rbp + 16]
        %define FN_ARG_6_W  WORD [rbp + 24]

        %define FN_ARG_1_D  ecx
        %define FN_ARG_2_D  edx
        %define FN_ARG_3_D  r8d
        %define FN_ARG_4_D  r9d
        %define FN_ARG_5_D  DWORD [rbp + 16]
        %define FN_ARG_6_D  DWORD [rbp + 24]

        %define FN_ARG_1_Q  rcx
        %define FN_ARG_2_Q  rdx
        %define FN_ARG_3_Q  r8
        %define FN_ARG_4_Q  r9
        %define FN_ARG_5_Q  QWORD [rbp + 16]
        %define FN_ARG_6_Q  QWORD [rbp + 24]

        %define FN_ARG_1_REGISTER   FN_ARG_1_Q
        %define FN_ARG_2_REGISTER   FN_ARG_2_Q
        %define FN_ARG_3_REGISTER   FN_ARG_3_Q
        %define FN_ARG_4_REGISTER   FN_ARG_4_Q

        ; Arguments 5+ are passed on the stack, unlike the GNU calling convention
        ; which supports passing 6 arguments in registers.
    %else
        %define FN_ARG_1_B  dil
        %define FN_ARG_2_B  sil
        %define FN_ARG_3_B  dl
        %define FN_ARG_4_B  cl
        %define FN_ARG_5_B  r8b
        %define FN_ARG_6_B  r9b

        %define FN_ARG_1_W  di
        %define FN_ARG_2_W  si
        %define FN_ARG_3_W  dx
        %define FN_ARG_4_W  cx
        %define FN_ARG_5_W  r8w
        %define FN_ARG_6_W  r9w

        %define FN_ARG_1_D  edi
        %define FN_ARG_2_D  esi
        %define FN_ARG_3_D  edx
        %define FN_ARG_4_D  ecx
        %define FN_ARG_5_D  r8d
        %define FN_ARG_6_D  r9d

        %define FN_ARG_1_Q  rdi
        %define FN_ARG_2_Q  rsi
        %define FN_ARG_3_Q  rdx
        %define FN_ARG_4_Q  rcx
        %define FN_ARG_5_Q  r8
        %define FN_ARG_6_Q  r9

        %define FN_ARG_1_REGISTER   FN_ARG_1_Q
        %define FN_ARG_2_REGISTER   FN_ARG_2_Q
        %define FN_ARG_3_REGISTER   FN_ARG_3_Q
        %define FN_ARG_4_REGISTER   FN_ARG_4_Q
        %define FN_ARG_5_REGISTER   FN_ARG_5_Q
        %define FN_ARG_6_REGISTER   FN_ARG_6_Q
    %endif
%elif __BITS__ == 32
    %define REGISTER_AX     eax
    %define REGISTER_BX     ebx
    %define REGISTER_CX     ecx
    %define REGISTER_DX     edx

    %if INTERNALS_USE_FASTCALL
        %define FN_ARG_1_B  cl
        %define FN_ARG_2_B  dl
        %define FN_ARG_3_B  BYTE [ebp + 8]
        %define FN_ARG_4_B  BYTE [ebp + 12]
        %define FN_ARG_5_B  BYTE [ebp + 16]
        %define FN_ARG_6_B  BYTE [ebp + 20]

        %define FN_ARG_1_W  cx
        %define FN_ARG_2_W  dx
        %define FN_ARG_3_W  WORD [ebp + 8]
        %define FN_ARG_4_W  WORD [ebp + 12]
        %define FN_ARG_5_W  WORD [ebp + 16]
        %define FN_ARG_6_W  WORD [ebp + 20]

        %define FN_ARG_1_D  ecx
        %define FN_ARG_2_D  edx
        %define FN_ARG_3_D  DWORD [ebp + 8]
        %define FN_ARG_4_D  DWORD [ebp + 12]
        %define FN_ARG_5_D  DWORD [ebp + 16]
        %define FN_ARG_6_D  DWORD [ebp + 20]
    %else
        %define FN_ARG_1_B  BYTE [ebp + 8]
        %define FN_ARG_2_B  BYTE [ebp + 12]
        %define FN_ARG_3_B  BYTE [ebp + 16]
        %define FN_ARG_4_B  BYTE [ebp + 20]
        %define FN_ARG_5_B  BYTE [ebp + 24]
        %define FN_ARG_6_B  BYTE [ebp + 28]

        %define FN_ARG_1_W  WORD [ebp + 8]
        %define FN_ARG_2_W  WORD [ebp + 12]
        %define FN_ARG_3_W  WORD [ebp + 16]
        %define FN_ARG_4_W  WORD [ebp + 20]
        %define FN_ARG_5_W  WORD [ebp + 24]
        %define FN_ARG_6_W  WORD [ebp + 28]

        %define FN_ARG_1_D  DWORD [ebp + 8]
        %define FN_ARG_2_D  DWORD [ebp + 12]
        %define FN_ARG_3_D  DWORD [ebp + 16]
        %define FN_ARG_4_D  DWORD [ebp + 20]
        %define FN_ARG_5_D  DWORD [ebp + 24]
        %define FN_ARG_6_D  DWORD [ebp + 28]
    %endif
%else
    %define REGISTER_AX     ax
    %define REGISTER_BX     bx
    %define REGISTER_CX     cx
    %define REGISTER_DX     dx

    %define FN_ARG_1_B  BYTE [bp + 4]
    %define FN_ARG_2_B  BYTE [bp + 6]
    %define FN_ARG_3_B  BYTE [bp + 8]
    %define FN_ARG_4_B  BYTE [bp + 10]
    %define FN_ARG_5_B  BYTE [bp + 12]
    %define FN_ARG_6_B  BYTE [bp + 14]

    %define FN_ARG_1_W  WORD [bp + 4]
    %define FN_ARG_2_W  WORD [bp + 6]
    %define FN_ARG_3_W  WORD [bp + 8]
    %define FN_ARG_4_W  WORD [bp + 10]
    %define FN_ARG_5_W  WORD [bp + 12]
    %define FN_ARG_6_W  WORD [bp + 14]
%endif

%endif  ; INCLUDE_METALC_X86_METALC_ASM_INC_
