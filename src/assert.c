#include <metalc/assert.h>
#include <metalc/metalc.h>
#include <metalc/signal.h>
#include <metalc/stdbool.h>
#include <metalc/stddef.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>

void mcinternal_assert(int expression, int line, const char *file,
                       const char *assert_text, const char *message, ...)
{
    mclib_FILE *out;
    va_list args;

    if (expression)
        return;

#if METALC_COMPILE_OPTION_ENABLE_FILE_IO
    out = (mclib_stderr != mclib_NULL) ? mclib_stderr : mclib_stdout;
    if (out)
    {
        fprintf(out, "Debug assertion failed on line %d in file %s: %s\n", line, file,
                assert_text);

        if (message)
        {
            va_start(args, message);
            vfprintf(out, message, args);
            va_end(args);
        }
    }
#else
    (void)out, (void)line, (void)file, (void)assert_text, (void)message, (void)args;
#endif

    abort();
}
