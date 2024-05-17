#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

extern int mclib_errno;

extern FILE *test_output_fd;

void write_csv_string(const char *text)
{
    int i;

    fputc('"', test_output_fd);

    /* Note: We add i >= 0 to prevent underflow if the string isn't terminated
     * by a null after ~2GiB. */
    for (i = 0; (text[i] != '\0') && (i >= 0); ++i)
    {
        if (text[i] == '"')
            fwrite("\"\"", 2, 1, test_output_fd);
        else
            fputc(text[i], test_output_fd);
    }
    fputc('"', test_output_fd);
}

void initialize_test_log(void)
{
    fprintf(
        test_output_fd,
        "status\ttest_name\ttest_file\tassertion_line\tmetalc_errno\tassertion_text\n");
}

void log_message(const char *level, const char *test_name, unsigned line,
                 const char *filename, const char *message, ...)
{
    va_list args;

    write_csv_string(level);
    fputc('\t', test_output_fd);

    write_csv_string(test_name);
    fputc('\t', test_output_fd);

    if (filename != NULL)
        write_csv_string(filename);
    fputc('\t', test_output_fd);

    fprintf(test_output_fd, "%u\t%d\t", line, mclib_errno);

    if (message != NULL)
    {
        va_start(args, message);
        vfprintf(test_output_fd, message, args);
    }
    fputc('\n', test_output_fd);
}

void log_raw_message(const char *level, const char *test_name, unsigned line,
                     const char *filename, const char *message)
{
    write_csv_string(level);
    fputc('\t', test_output_fd);

    write_csv_string(test_name);
    fputc('\t', test_output_fd);

    if (filename != NULL)
        write_csv_string(filename);
    fputc('\t', test_output_fd);

    fprintf(test_output_fd, "%u\t%d\t", line, mclib_errno);

    if (message != NULL)
        fprintf(test_output_fd, "%s", message);
    fputc('\n', test_output_fd);
}
