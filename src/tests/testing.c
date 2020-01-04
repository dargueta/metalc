#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>

#include <metalc/stdlib.h>

extern int test_output_fd;


void write_csv_string(const char *text) {
    int i;

    write(test_output_fd, "\"", 1);

    /* Note: We add i >= 0 to prevent underflow if the string isn't terminated
     * by a null after ~2GiB. */
    for (i = 0; (text[i] != '\0') && (i >= 0); ++i) {
        if (text[i] == '"')
            write(test_output_fd, "\"\"", 2);
        else
            write(test_output_fd, &text[i], 1);
    }
    write(test_output_fd, "\"", 1);
}


void log_message(
    const char *level,
    const char *test_name,
    unsigned line,
    const char *filename,
    const char *message
) {
    char buffer[128];

    write_csv_string(level);
    write(test_output_fd, ",", 1);

    write_csv_string(test_name);
    write(test_output_fd, ",", 1);

    if (filename != NULL)
        write_csv_string(filename);
    write(test_output_fd, ",", 1);

    utoa(line, buffer, 10);
    write_csv_string(buffer);
    write(test_output_fd, ",", 1);

    if (message != NULL)
        write_csv_string(message);
    write(test_output_fd, "\x0a", 1);
}
