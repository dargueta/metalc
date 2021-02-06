#ifndef INCLUDE_METALC_TESTING_H_
#define INCLUDE_METALC_TESTING_H_

METALC_INTERNAL_WITH_ATTR(nonnull)
extern void testhook_log_message(const char *file, int line, const char *message);

typedef int (* metalc_unit_test_fn)(int, char **, char **);

struct UnitTestEntry {
    metalc_unit_test_fn function;
    const char *name;
};


#define log_message(msg)            testhook_log_message(__FILE__, __LINE__, (msg))
#define log_begin_test(name)        log_message("begin-test\t" #name)
#define log_end_test()              log_message("end-test\t")
#define log_assertion(msg)          log_message("assert-success\t" #msg)
#define log_failed_assertion(msg)   log_message("assert-failed\t" #msg)


#define assert(expression)  if (!(expression)) {                    \
                                log_failed_assertion(#expression);  \
                                log_end_test();                     \
                                return -1;                          \
                            }                                       \
                            log_assertion(#expression)


#define BEGIN_TEST(name)    \
    int (name)(int argc, char **argv, char **env) { \
        (void)argc, (void)argv, (void)env;          \
        log_begin_test(name);

#define END_TEST()      log_end_test(); return 0; }


#endif  /* INCLUDE_METALC_TESTING_H_ */
