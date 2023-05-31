/* This file is compiled for the target machine being tested on and runs exactly
 * one test case.
 *
 * It's compiled in standalone mode*/

#include "include/testing.h"
#include <metalc/crtinit.h>


#define _STR(x)     #x


extern int test_function(struct TestResult *result);


static unsigned strlen_equivalent(const char *string) {
    unsigned length;

    for (length = 0; string[length] != '\0'; length++)
        ;
    return length;
}


static void strncpy_equivalent(char *dest, const char *src, unsigned max) {
    unsigned i;
    for (i = 0; i < max; ++i) {
        dest[i] = src[i];
        if (src[i] == '\0')
            break;
    }
}


static void memset_equivalent(void *dest, int value, unsigned size) {
    unsigned i;
    for (i = 0; i < size; ++i)
        ((char *)dest)[i] = (char)value;
}


static const char kHexAlphabet[] = "0123456789ABCDEF";
static void int_to_hex(char *dest, unsigned value, unsigned max) {
    int i;

    memset_equivalent(dest, '0', max);
    for (i = (int)max - 1; i >= 0; --i) {
        dest[i] = kHexAlphabet[value % 16];
        value /= 16;
    }
}


void init_test_result(struct TestResult *t, const char *name) {
    memset_equivalent(t, 0, sizeof(*t));
    strncpy_equivalent(t->test_name, name, sizeof(t->test_name));
}


void log_test_failed(
    struct TestResult *result,
    const char *assertion_text,
    const char *file,
    unsigned int line_number
) {
    strncpy_equivalent(
        result->assertion_text, assertion_text, sizeof(result->assertion_text)
    );
    strncpy_equivalent(result->filename, file, sizeof(result->filename));
    int_to_hex(result->line_number, line_number, sizeof(result->line_number));
}


int fake_main(int argc, char **argv, char **env) {
    (void)argc, (void)env;
    return test_function((struct TestResult *)argv[0]);
}


struct TestResult result;

int entry_point(struct TestResult *t) {
    MetalCRuntimeInfo rti;
    char *argv[2];

    argv[0] = (char *)t;
    argv[1] = NULL;

    if (strlen_equivalent(_STR(METALC_TEST_NAME)) > METALC_TEST_NAME_MAX_LENGTH) {
        log_test_failed(
            t,
            "Test name >" _STR(METALC_TEST_NAME_MAX_LENGTH) " chars " _STR(METALC_TEST_NAME),
            __FILE__,
            0
        );
        return -1;
    }

    rti.udata = NULL;
    rti.page_size = 4096;
    rti.main = fake_main;
    rti.stdin_handle = 0;
    rti.stdout_handle = 0;
    rti.stderr_handle = 0;

    cstdlib_init(&rti);
    cstdlib_run(1, argv, NULL);
    return rti.main_return_value;
}
