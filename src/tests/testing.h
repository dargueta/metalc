#ifndef INCLUDE_METALC_TESTING_H_
#define INCLUDE_METALC_TESTING_H_


typedef int (* metalc_unit_test_fn)(int, char **, char **);

struct UnitTestEntry {
    metalc_unit_test_fn function;
    const char *name;
};


void initialize_test_log(void);

void log_message(
    const char *level,
    const char *test_name,
    unsigned line,
    const char *filename,
    const char *message,
    ...
);


void log_raw_message(
    const char *level,
    const char *test_name,
    unsigned line,
    const char *filename,
    const char *message
);



#define info_message(msg, ...)  log_message("INFO", _test_name, __LINE__, __FILE__, (msg), __VA_ARGS__)


#define ASSERT_MSG(expr, msg, ...)                                      \
    if (expr)                                                           \
        log_raw_message("OK", _test_name,  __LINE__, __FILE__, #expr);  \
    else {                                                              \
        log_message("FAILED", _test_name, __LINE__, __FILE__, (msg), __VA_ARGS__);   \
        return 1;                                                       \
    }


#define ASSERT(expr)                                                        \
    if (expr)                                                               \
        log_raw_message("OK", _test_name,  __LINE__, __FILE__, #expr);      \
    else {                                                                  \
        log_raw_message("FAILED", _test_name, __LINE__, __FILE__, #expr);   \
        return 1;                                                           \
    }


#define CHECK_EQ(x, y)  ASSERT_MSG(((x) == (y)), "Assertion failed: %s == %s -- left=%d, right=%d", #x, #y, x, y)
#define CHECK_NE(x, y)  ASSERT_MSG(((x) != (y)), "Assertion failed: %s != %s -- left=%d, right=%d", #x, #y, x, y)
#define CHECK_GT(x, y)  ASSERT_MSG(((x) > (y)), "Assertion failed: %s > %s -- left=%d, right=%d", #x, #y, x, y)
#define CHECK_GE(x, y)  ASSERT_MSG(((x) >= (y)), "Assertion failed: %s >= %s -- left=%d, right=%d", #x, #y, x, y)
#define CHECK_LT(x, y)  ASSERT_MSG(((x) < (y)), "Assertion failed: %s < %s -- left=%d, right=%d", #x, #y, x, y)
#define CHECK_LE(x, y)  ASSERT_MSG(((x) <= (y)), "Assertion failed: %s <= %s -- left=%d, right=%d", #x, #y, x, y)

#define CHECK_EQ_MSG(x, y, msg)  ASSERT_MSG(((x) == (y)), "%s", (msg))
#define CHECK_NE_MSG(x, y, msg)  ASSERT_MSG(((x) != (y)), "%s", (msg))
#define CHECK_GT_MSG(x, y, msg)  ASSERT_MSG(((x) > (y)), "%s", (msg))
#define CHECK_GE_MSG(x, y, msg)  ASSERT_MSG(((x) >= (y)), "%s", (msg))
#define CHECK_LT_MSG(x, y, msg)  ASSERT_MSG(((x) < (y)), "%s", (msg))
#define CHECK_LE_MSG(x, y, msg)  ASSERT_MSG(((x) <= (y)), "%s", (msg))

#define INFO(msg)   log_message("INFO", _test_name, __LINE__, __FILE__, (msg))


#define BEGIN_TEST(name)    \
    int (name)(int argc, char **argv, char **env) {  \
        (void)argc, (void)argv, (void)env;          \
        static const char *_test_name = #name;

#define END_TEST()      return 0; }


#endif  /* INCLUDE_METALC_TESTING_H_ */
