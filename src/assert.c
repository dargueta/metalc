#include <metalc/assert.h>
#include <metalc/metalc.h>
#include <metalc/signal.h>
#include <metalc/stdbool.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>


void __mcint_assert(
    int expression, int line, const char *function, const char *file,
    const char* assert_text, const char *message, ...
) {
    __mcapi_FILE *out;
    va_list args;

    if (expression)
        return;

    #if METALC_COMPILE_OPTION_ENABLE_FILE_IO
        out = (stderr != NULL) ? stderr : stdout;
        if (out) {
            fprintf(
                out,
                "Debug assertion failed in function %s on line %d in file %s: %s\n",
                function,
                line,
                file,
                assert_text
            );

            if (message) {
                va_start(args, message);
                vfprintf(out, args);
                va_end(args);
            }
        }
    #else
        (void)out, (void)message, (void)args;
    #endif

    abort();
}

cstdlib_implement(__mcint_assert);
