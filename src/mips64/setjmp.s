.include "metalc/mips/metalc.s"

.globl __mcapi_setjmp
.globl __mcapi_longjmp

.section .text

__mcapi_setjmp:
    # $a0 contains the jump buffer
    sd  $s0, 0($a0)
    sd  $s1, 8($a0)
    sd  $s2, 16($a0)
    sd  $s3, 24($a0)
    sd  $s4, 32($a0)
    sd  $s5, 40($a0)
    sd  $s6, 48($a0)
    sd  $s7, 56($a0)
    sd  $sp, 64($a0)
    sd  $fp, 72($a0)
    sd  $gp, 80($a0)
    sd  $ra, 88($a0)

    # TODO (dargueta): Do we need to store the exception register(s) and stuff?
    .if METALC_COMPILE_FOR_KERNEL
        sd  $k0, 96($a0)
        sd  $k1, 104($a0)
    .endif

    li  $v0, 0
    jr  $ra


__mcapi_longjmp:
    # $a0 contains the jump buffer, $a1 is the return value.
    ld  $s0, 0($a0)
    ld  $s1, 8($a0)
    ld  $s2, 16($a0)
    ld  $s3, 24($a0)
    ld  $s4, 32($a0)
    ld  $s5, 40($a0)
    ld  $s6, 48($a0)
    ld  $s7, 56($a0)
    ld  $sp, 64($a0)
    ld  $fp, 72($a0)
    ld  $gp, 80($a0)
    ld  $ra, 88($a0)

    # TODO (dargueta) when compiling in kernel mode, restore $k0 and $k1.
    .if METALC_COMPILE_FOR_KERNEL
        ld  $k0, 96($a0)
        ld  $k1, 104($a0)
    .endif

    move    $v0, $a1
    jr  $ra
