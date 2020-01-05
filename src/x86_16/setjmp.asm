bits 16

%include "metalc/setjmp.inc"

global __mcapi_setjmp
global __mcapi_longjmp


__mcapi_setjmp:
    mov     cx, bp
    mov     bp, sp

    ; Save return address in AX because we won't be able to access it after we
    ; make bp point at the jmp_buf struct.
    mov     ax, [bp]

    mov     bp, [bp + 2]
    mov     [bp + tJmpBuf.j_return], ax
    mov     [bp + tJmpBuf.j_bx], bx
    mov     [bp + tJmpBuf.j_sp], sp
    mov     [bp + tJmpBuf.j_si], si
    mov     [bp + tJmpBuf.j_di], di
    mov     [bp + tJmpBuf.j_bp], cx     ; Remember, we saved BP into CX earlier

    ; Set BP back to its original value
    mov     bp, cx

    ; Always return 0. Assuming an integer is 32 bits we return it in DX:AX so
    ; we need to clear both.
    xor     ax, ax
    xor     dx, dx
    ret     2


__mcapi_longjmp:
    mov     bp, sp

    ; Set the return value first before we overwrite BP. It's a 32-bit integer
    ; so we need to set DX:AX.
    mov     ax, [bp + 4]
    mov     dx, [bp + 6]

    ; Point bp to the jmp_buf struct
    mov     bp, [bp + 2]

    ; Overwrite the return address
    mov     cx, [bp + tJmpBuf.j_return]
    mov     si, sp
    mov     [si], cx

    ; Reset all the registers we saved
    mov     bx, [bp + tJmpBuf.j_bx]
    mov     sp, [bp + tJmpBuf.j_sp]
    mov     si, [bp + tJmpBuf.j_si]
    mov     di, [bp + tJmpBuf.j_di]
    mov     bp, [bp + tJmpBuf.j_bp]
    ret     6
