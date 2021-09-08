#ifndef INCLUDE_METALC_TESTING_H_
#define INCLUDE_METALC_TESTING_H_

#include "metalc/crtinit.h"

extern MetalCRuntimeInfo *__mcint_runtime_info;

METALC_INTERNAL_WITH_ATTR(nonnull)
extern void testhook_register_test(const char *name, int id);

METALC_INTERNAL_WITH_ATTR(nonnull)
extern void testhook_begin_test(int id);

METALC_INTERNAL_WITH_ATTR(nonnull)
extern void testhook_end_test(int id);

METALC_INTERNAL_WITH_ATTR(nonnull)
extern void testhook_assertion_failed(
    int test_id, const char *file, int line, const char *expr
);

typedef int (* metalc_unit_test_fn)(int, char **, char **);

struct UnitTestEntry {
    metalc_unit_test_fn function;
    const char *name;
};


#define TEST_ID                     ((int)((intptr_t)__mcint_runtime_info->udata))
#define log_begin_test()            testhook_begin_test(TEST_ID)
#define log_end_test()              testhook_end_test(TEST_ID)
#define log_failed_assertion(msg)   testhook_assertion_failed(TEST_ID, __FILE__, __LINE__, msg)


#define check(expression)   if (!(expression)) {                    \
                                log_failed_assertion(#expression);  \
                                log_end_test();                     \
                                return -1;                          \
                            }


#define BEGIN_TEST(name)    \
    int (name)(int argc, char **argv, char **env) { \
        (void)argc, (void)argv, (void)env;          \
        testhook_register_test(#name, TEST_ID);     \
        log_begin_test();

#define END_TEST()      log_end_test(); return 0; }


#endif  /* INCLUDE_METALC_TESTING_H_ */
