; ============================================================================ ;
; Partial port of the C++11 <atomic> library to C.                             ;
;                                                                              ;
; This isn't a full backport and isn't part of the standard C library either,  ;
; so don't use this in code that needs to be portable.                         ;
;                                                                              ;
; @file atomic.asm                                                             ;
; ============================================================================ ;

bits 64

%include "metalc/x86/metalc.inc"

struc tAtomicObject
    .value:   resq 1
    .status:  resd 1
endstruc

global atomic_flag_test_and_set:function
global atomic_flag_clear:function

global atomic_load_8:function
global atomic_load_16:function
global atomic_load_32:function
global atomic_load_64:function
global atomic_store_8:function
global atomic_store_16:function
global atomic_store_32:function
global atomic_store_64:function
global atomic_exchange_8:function
global atomic_exchange_16:function
global atomic_exchange_32:function
global atomic_exchange_64:function


%macro _acquire_lock_spinwait 0
    %%begin:
    mfence
    lock bts    DWORD [FN_ARG_1_Q + tAtomicObject.status], 0
    pause
    jc      %%begin
%endmacro

; Release the lock by clearing the low bit. Upper bits are preserved to allow
; them to be used for something else by other code.
%define _release_lock   lock and    DWORD [FN_ARG_1_Q + tAtomicObject.status], 0xfffffffe


atomic_flag_test_and_set:
    mfence
    lock bts    DWORD [FN_ARG_1_Q], 0
    jc      .set_rax

    ; Bit was originally cleared; clear all bits of RAX to indicate FALSE
    xor     rax, rax
    ret

    .set_rax:
    ; Bit was originally set; RAX to 1 to indicate TRUE
    mov     rax, 1
    ret


atomic_flag_clear:
    mfence
    lock and    DWORD [FN_ARG_1_Q], 0xfffffffe
    ret


%macro m_atomic_load 1
    _acquire_lock_spinwait
    mov     %1, [FN_ARG_1_Q + tAtomicObject.value]
    _release_lock
    ret
%endmacro


%macro m_atomic_store 1
    _acquire_lock_spinwait
    mov     [FN_ARG_1_Q + tAtomicObject.value], %1
    _release_lock
    ret
%endmacro


%macro m_atomic_exchange 2
    _acquire_lock_spinwait
    mov     %2, [FN_ARG_1_Q + tAtomicObject.value]
    mov     [FN_ARG_1_Q + tAtomicObject.value], %1
    _release_lock
    ret
%endmacro


atomic_load_8:      m_atomic_load al
atomic_load_16:     m_atomic_load ax
atomic_load_32:     m_atomic_load eax
atomic_load_64:     m_atomic_load rax

atomic_store_8:     m_atomic_store FN_ARG_2_B
atomic_store_16:    m_atomic_store FN_ARG_2_W
atomic_store_32:    m_atomic_store FN_ARG_2_D
atomic_store_64:    m_atomic_store FN_ARG_2_Q

atomic_exchange_8:  m_atomic_exchange FN_ARG_2_B, al
atomic_exchange_16: m_atomic_exchange FN_ARG_2_W, ax
atomic_exchange_32: m_atomic_exchange FN_ARG_2_D, eax
atomic_exchange_64: m_atomic_exchange FN_ARG_2_Q, rax
