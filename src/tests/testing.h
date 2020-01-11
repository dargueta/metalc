#ifndef INCLUDE_METALC_TESTING_H_
#define INCLUDE_METALC_TESTING_H_


typedef int (* metalc_unit_test_fn)(int, char **, char **);

struct UnitTestEntry {
    metalc_unit_test_fn function;
    const char *name;
};


void log_message(
    const char *level,
    const char *test_name,
    unsigned line,
    const char *filename,
    const char *message
);


#define ASSERT_MSG(expr, msg)                                           \
    if (expr)                                                           \
        log_message("OK", _test_name,  __LINE__, __FILE__, "");         \
    else {                                                              \
        log_message("FAILED", _test_name, __LINE__, __FILE__, (msg));   \
        return 1;                                                       \
    }


#define ASSERT(expr)    ASSERT_MSG((expr), NULL)

#define CHECK_EQ(x, y)  ASSERT((x) == (y))
#define CHECK_NE(x, y)  ASSERT((x) != (y))
#define CHECK_GT(x, y)  ASSERT((x) > (y))
#define CHECK_GE(x, y)  ASSERT((x) >= (y))
#define CHECK_LT(x, y)  ASSERT((x) < (y))
#define CHECK_LE(x, y)  ASSERT((x) <= (y))

#define CHECK_EQ_MSG(x, y, msg)  ASSERT_MSG((x) == (y), (msg))
#define CHECK_NE_MSG(x, y, msg)  ASSERT_MSG((x) != (y), (msg))
#define CHECK_GT_MSG(x, y, msg)  ASSERT_MSG((x) > (y), (msg))
#define CHECK_GE_MSG(x, y, msg)  ASSERT_MSG((x) >= (y), (msg))
#define CHECK_LT_MSG(x, y, msg)  ASSERT_MSG((x) < (y), (msg))
#define CHECK_LE_MSG(x, y, msg)  ASSERT_MSG((x) <= (y), (msg))

#define INFO(msg)   log_message("INFO", _test_name, __LINE__, __FILE__, (msg))


#define BEGIN_TEST(name)    \
    int (name)(int argc, char **argv, char **env) {  \
        (void)argc, (void)argv, (void)env;          \
        static const char *_test_name = #name;

#define END_TEST()      return 0; }


#endif  /* INCLUDE_METALC_TESTING_H_ */
