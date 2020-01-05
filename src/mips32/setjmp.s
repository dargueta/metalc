.globl __mcapi_setjmp
.globl __mcapi_longjmp

.section .text

__mcapi_setjmp:
    # $a0 contains the jump buffer
    sw  $s0, 0($a0)
    sw  $s1, 4($a0)
    sw  $s2, 8($a0)
    sw  $s3, 12($a0)
    sw  $s4, 16($a0)
    sw  $s5, 20($a0)
    sw  $s6, 24($a0)
    sw  $s7, 28($a0)
    sw  $sp, 32($a0)
    sw  $fp, 36($a0)
    sw  $gp, 40($a0)
    sw  $ra, 44($a0)

    # TODO (dargueta): Do we need to store the exception register(s) and stuff?
    .if METALC_COMPILE_FOR_KERNEL
        sw  $k0, 48($a0)
        sw  $k1, 52($a0)
    .endif

    li  $v0, 0
    jr  $ra


__mcapi_longjmp:
    # $a0 contains the jump buffer, $a1 is the return value.
    lw  $s0, 0($a0)
    lw  $s1, 4($a0)
    lw  $s2, 8($a0)
    lw  $s3, 12($a0)
    lw  $s4, 16($a0)
    lw  $s5, 20($a0)
    lw  $s6, 24($a0)
    lw  $s7, 28($a0)
    lw  $sp, 32($a0)
    lw  $fp, 36($a0)
    lw  $gp, 40($a0)
    lw  $ra, 44($a0)

    .if METALC_COMPILE_FOR_KERNEL
        lw  $k0, 48($a0)
        lw  $k1, 52($a0)
    .endif

    move    $v0, $a1
    jr  $ra
