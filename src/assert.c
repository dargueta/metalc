#include <stdbool.h>

#include <metalc/assert.h>
#include <metalc/signal.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>


extern const void *__mclib_abort_target;


void __mcint_assert(int expression, int line, const char *function, const char *file) {
    __mcapi_FILE *out;

    if (expression)
        return;

#if METALC_COMPILE_OPTION_ENABLE_FILE_IO
    out = (stderr) ? stderr : stdout;
    if (out) {
        fprintf(
            out,
            "Debug assertion failed in function %s on line %d in file %s.\n",
            function,
            line,
            file
        );
    }
#else
    (void)out, (void)line, (void)function, (void)file;
#endif

    abort();
}
