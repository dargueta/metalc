#include <metalc/assert.h>
#include <metalc/metalc.h>
#include <metalc/signal.h>
#include <metalc/stdbool.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>


void __mcint_assert(
    int expression, int line, const char *function, const char *file,
    const char* assert_text
) {
    __mcapi_FILE *out;

    if (expression)
        return;

#if METALC_COMPILE_OPTION_ENABLE_FILE_IO
    out = (stderr) ? stderr : stdout;
    if (out) {
        fprintf(
            out,
            "Debug assertion failed in function %s on line %d in file %s: %s\n",
            function,
            line,
            file,
            assert_text
        );
    }
#else
    (void)out, (void)line, (void)function, (void)file, (void)assert_text;
#endif

    abort();
}
cstdlib_implement(__mcint_assert);
