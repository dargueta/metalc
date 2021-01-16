#ifndef INCLUDE_METALC_TESTING_H_
#define INCLUDE_METALC_TESTING_H_


#define METALC_LOG_LEVEL_DEBUG      0
#define METALC_LOG_LEVEL_INFO       10
#define METALC_LOG_LEVEL_WARNING    20
#define METALC_LOG_LEVEL_ERROR      30
#define METALC_LOG_LEVEL_CRITICAL   40


METALC_API_INTERNAL_WITH_ATTR(noreturn) extern void testhook_abort(int line, const char *file, const char *assert_text) __attribute__((noreturn));
METALC_API_INTERNAL extern int testhook_report_test_name(int test_id, const char *test_name);
METALC_API_INTERNAL extern int testhook_log(int level, const char *file, int line, const char *message);
METALC_API_INTERNAL extern int testhook_report_result(int test_id, int result);
METALC_API_INTERNAL_WITH_ATTR(noreturn) extern int testhook_terminate(int sig);
METALC_API_INTERNAL extern void testhook_signal(int sig);


typedef int (* metalc_unit_test_fn)(int, char **, char **);

struct UnitTestEntry {
    metalc_unit_test_fn function;
    const char *name;
};


void log_message(
    int level,
    const char *test_name,
    unsigned line,
    const char *filename,
    const char *message,
    ...
);


#define info_message(msg, ...)  log_message(METALC_LOG_LEVEL_INFO, _test_name, __LINE__, __FILE__, (msg), __VA_ARGS__)


#define INFO(msg)   log_message(METALC_LOG_LEVEL_INFO, _test_name, __LINE__, __FILE__, (msg))


#define BEGIN_TEST(name)    \
    int (name)(int argc, char **argv, char **env) {  \
        (void)argc, (void)argv, (void)env;          \
        static const char *_test_name = #name;

#define END_TEST()      return 0; }


#endif  /* INCLUDE_METALC_TESTING_H_ */
