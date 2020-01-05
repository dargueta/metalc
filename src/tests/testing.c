#include <stdio.h>
#include <stdlib.h>

extern FILE *test_output_fd;


void write_csv_string(const char *text) {
    int i;

    fputc('"', test_output_fd);

    /* Note: We add i >= 0 to prevent underflow if the string isn't terminated
     * by a null after ~2GiB. */
    for (i = 0; (text[i] != '\0') && (i >= 0); ++i) {
        if (text[i] == '"')
            fwrite("\"\"", 2, 1, test_output_fd);
        else
            fputc(text[i], test_output_fd);
    }
    fputc('"', test_output_fd);
}


void log_message(
    const char *level,
    const char *test_name,
    unsigned line,
    const char *filename,
    const char *message
) {
    write_csv_string(level);
    fputc(',', test_output_fd);

    write_csv_string(test_name);
    fputc(',', test_output_fd);

    if (filename != NULL)
        write_csv_string(filename);
    fputc(',', test_output_fd);

    fprintf(test_output_fd, "%u,", line);

    if (message != NULL)
        write_csv_string(message);
    fputc('\n', test_output_fd);
}
