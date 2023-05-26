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


#define INFO_MSG(msg, ...)  log_message("INFO", _test_name, __LINE__, __FILE__, (msg), __VA_ARGS__)


#define CHECK_MSG(expr, msg, ...)       \
    if (!(expr)) {                      \
        log_message("FAILED", _test_name, __LINE__, __FILE__, msg, __VA_ARGS__); \
        failed_flag = 1;                                    \
    }

#define CHECK(expr)                     \
    if (!(expr)) {                      \
        log_raw_message("FAILED", _test_name, __LINE__, __FILE__, #expr); \
        failed_flag = 1;                                    \
    }


#define REQUIRE_MSG(expr, msg, ...)                                     \
    if (!(expr)) {                                                      \
        log_message("FAILED", _test_name, __LINE__, __FILE__, msg, __VA_ARGS__);   \
        return 1;                                                       \
    }


#define REQUIRE(expr)                                                       \
    if (!(expr)) {                                                          \
        log_raw_message("FAILED", _test_name, __LINE__, __FILE__, #expr);   \
        return 1;                                                           \
    }


#define CHECK_EQ(x, y)  CHECK_MSG(((x) == (y)), "Assertion failed: %s == %s (left=%d, right=%d)", #x, #y, x, y)
#define CHECK_NE(x, y)  CHECK_MSG(((x) != (y)), "Assertion failed: %s != %s (left=%d, right=%d)", #x, #y, x, y)
#define CHECK_GT(x, y)  CHECK_MSG(((x) > (y)), "Assertion failed: %s > %s (left=%d, right=%d)", #x, #y, x, y)
#define CHECK_GE(x, y)  CHECK_MSG(((x) >= (y)), "Assertion failed: %s >= %s (left=%d, right=%d)", #x, #y, x, y)
#define CHECK_LT(x, y)  CHECK_MSG(((x) < (y)), "Assertion failed: %s < %s (left=%d, right=%d)", #x, #y, x, y)
#define CHECK_LE(x, y)  CHECK_MSG(((x) <= (y)), "Assertion failed: %s <= %s (left=%d, right=%d)", #x, #y, x, y)
#define CHECK_EQ_MSG(x, y, msg)  CHECK_MSG(((x) == (y)), "%s", (msg))
#define CHECK_NE_MSG(x, y, msg)  CHECK_MSG(((x) != (y)), "%s", (msg))
#define CHECK_GT_MSG(x, y, msg)  CHECK_MSG(((x) > (y)), "%s", (msg))
#define CHECK_GE_MSG(x, y, msg)  CHECK_MSG(((x) >= (y)), "%s", (msg))
#define CHECK_LT_MSG(x, y, msg)  CHECK_MSG(((x) < (y)), "%s", (msg))
#define CHECK_LE_MSG(x, y, msg)  CHECK_MSG(((x) <= (y)), "%s", (msg))


#define REQUIRE_EQ(x, y)  REQUIRE_MSG(((x) == (y)), "Assertion failed: %s == %s (left=%d, right=%d)", #x, #y, x, y)
#define REQUIRE_NE(x, y)  REQUIRE_MSG(((x) != (y)), "Assertion failed: %s != %s (left=%d, right=%d)", #x, #y, x, y)
#define REQUIRE_GT(x, y)  REQUIRE_MSG(((x) > (y)), "Assertion failed: %s > %s (left=%d, right=%d)", #x, #y, x, y)
#define REQUIRE_GE(x, y)  REQUIRE_MSG(((x) >= (y)), "Assertion failed: %s >= %s (left=%d, right=%d)", #x, #y, x, y)
#define REQUIRE_LT(x, y)  REQUIRE_MSG(((x) < (y)), "Assertion failed: %s < %s (left=%d, right=%d)", #x, #y, x, y)
#define REQUIRE_LE(x, y)  REQUIRE_MSG(((x) <= (y)), "Assertion failed: %s <= %s (left=%d, right=%d)", #x, #y, x, y)
#define REQUIRE_EQ_MSG(x, y, msg)  REQUIRE_MSG(((x) == (y)), "%s", (msg))
#define REQUIRE_NE_MSG(x, y, msg)  REQUIRE_MSG(((x) != (y)), "%s", (msg))
#define REQUIRE_GT_MSG(x, y, msg)  REQUIRE_MSG(((x) > (y)), "%s", (msg))
#define REQUIRE_GE_MSG(x, y, msg)  REQUIRE_MSG(((x) >= (y)), "%s", (msg))
#define REQUIRE_LT_MSG(x, y, msg)  REQUIRE_MSG(((x) < (y)), "%s", (msg))
#define REQUIRE_LE_MSG(x, y, msg)  REQUIRE_MSG(((x) <= (y)), "%s", (msg))


#define INFO(msg)   log_raw_message("INFO", _test_name, __LINE__, __FILE__, (msg))


#define BEGIN_TEST(name)    \
    static int (name)(int argc, char **argv, char **env) {  \
        (void)argc, (void)argv, (void)env;          \
        static const char *_test_name = #name;              \
        int failed_flag = 0;

#define END_TEST()  \
    log_raw_message("PASSED", _test_name, __LINE__, __FILE__, "");  \
    return failed_flag; }


#endif  /* INCLUDE_METALC_TESTING_H_ */
