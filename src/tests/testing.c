#include <metalc/stdarg.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>


void log_message(
    int level,
    const char *test_name,
    unsigned line,
    const char *filename,
    const char *message,
    ...
) {
    va_list args;
    char buffer[256];
    int write_length;

    write_length = snprintf(
        buffer, sizeof(buffer), "%s@%s[%u] -- ", test_name, filename, line
    );

    if (write_length < (sizeof(buffer) - 1)) {
        va_start(args, message);
        vsnprintf(
            buffer + write_length, sizeof(buffer) - write_length, message, args
        );
        va_end(args);
    }

    testhook_log(level, filename, line, buffer);
}
