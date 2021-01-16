%include "metalc/x86/metalc.inc"
%include "metalc/x86/setjmp.inc"


%if ARCHITECTURE_SIZE == 16
    bits 16

    %macro convert_1_arg 0
        mov     al, 1
    %endmacro

    %macro convert_2_arg 0
        mov     al, 2
    %endmacro
%elif ARCHITECTURE_SIZE == 32
    bits 32

    %macro convert_1_arg 0
        mov     al, 1
        push    FN_ARG_1_D
    %endmacro

    %macro convert_2_arg 0
        mov     al, 2
        push    FN_ARG_1_D
        push    FN_ARG_2_D
    %endmacro
%else
    bits 64

    %macro convert_1_arg 0
        mov     al, 1
        push    FN_ARG_1_Q
    %endmacro

    %macro convert_2_arg 0
        mov     al, 2
        push    FN_ARG_1_Q
        push    FN_ARG_2_Q
    %endmacro
%endif


; int testhook_terminate(int test_id, int sig);
testhook_abort:
    convert_2_arg
    int     0x80


; int testhook_signal(int test_id, int sig);
testhook_record_signal:
    convert_2_arg
    int     0x81


; int testhook_report_test_name(int id, const char *test_name);
testhook_report_test_name:
    convert_2_arg
    int     0x82


; int testhook_report_test_begin(int test_id);
testhook_report_test_begin:
    convert_1_arg
    int     0x83


; void testhook_report_test_succeeded(int test_id);
testhook_report_test_succeeded:
    convert_1_arg
    int     0x84


; void testhook_report_test_failed(int test_id);
testhook_report_test_failed:
    convert_1_arg
    int     0x85
