#ifndef INCLUDE_METALC_TESTING_H_
#define INCLUDE_METALC_TESTING_H_

#ifndef METALC_TEST_NAME
    #error "METALC_TEST_NAME is not defined. It must be passed to the compiler."
#endif

#ifndef METALC_TEST_NAME_MAX_LENGTH
    #define METALC_TEST_NAME_MAX_LENGTH 127
#endif

#define _STR(x)     #x


typedef int (* metalc_unit_test_fn)(int, char **, char **);

struct UnitTestEntry {
    metalc_unit_test_fn function;
    const char *name;
};


struct TestResult {
    char test_name[METALC_TEST_NAME_MAX_LENGTH + 1];
    char filename[128];
    char assertion_text[256];
    char line_number[8];
    char status;
};


void init_test_result(struct TestResult *t, const char *name);

void log_test_failed(
    struct TestResult *t,
    const char *assertion_text,
    const char *file,
    unsigned int line_number
);


#define BEGIN_TEST()        int test_function(struct TestResult *t) {   \
                                init_test_result(t, _STR(METALC_TEST_NAME)); \

#define END_TEST()          return 0; }

#define check(expr)     if (!(expr)) { \
                            log_test_failed(t, #expr, __FILE__, __LINE__); \
                            return 1; \
                        }

#endif  /* INCLUDE_METALC_TESTING_H_ */
