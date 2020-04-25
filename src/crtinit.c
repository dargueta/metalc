#include <stddef.h>
#include <limits.h>

#include <metalc/crtinit.h>
#include <metalc/errno.h>
#include <metalc/locale.h>
#include <metalc/metalc.h>
#include <metalc/setjmp.h>


extern int malloc_init(void);
extern int malloc_teardown(void);
extern int stdio_init(void);
extern int stdio_teardown(void);


MetalCRuntimeInfo *__mcint_runtime_info __attribute__((visibility("hidden"))) = NULL;
__mcapi_jmp_buf __mcint_abort_target;


static int crt_init(void) {
    /* Die if cstdlib_start hasn't been called yet. We need the kernel to give us the
     * runtime info first. */
    if (__mcint_runtime_info == NULL)
        return __mcapi_EFAULT;

    __mcapi_errno = 0;
    setlocale(__mcapi_LC_ALL, "C");
    malloc_init();
    stdio_init();
    /* TODO (dargueta): Initialize atexit here. */

    return 0;
}


static int crt_teardown(void) {
    stdio_teardown();
    malloc_teardown();
    return 0;
}


int cstdlib_start(MetalCRuntimeInfo *rti, int argc, char **argv, char **env) {
    int result;

    __mcint_runtime_info = rti;

    result = crt_init();
    if (result != 0) {
        /* Failed to initialize the standard library. The kernel is responsible
         * for taking the appropriate action. */
        rti->main_return_value = -1;
        rti->signal_code = -1;
        return result;
    }

    result = setjmp(__mcint_abort_target);
    if (result == 0) {
        /* Call main() using the three-argument form. It's up to the kernel to
         * provide a shim for main() implementations that take zero or two
         * arguments. */
        rti->main_return_value = rti->main(argc, argv, env);

        /* If we get here then main() returned normally. An abnormal termination
         * uses longjmp to jump to the abort target above, using the triggered
         * signal as the return value. */
        rti->signal_code = 0;
    }
    else if (result == INT_MIN)
        /* exit() was called, rti->main_return_value is already set. */
        rti->signal_code = 0;
    else {
        /* If we get here then main() was terminated by an uncaught signal, and
         * `result` is the signal number. */
        rti->signal_code = result;
        rti->main_return_value = -1;
    }

    crt_teardown();
    return 0;
}
