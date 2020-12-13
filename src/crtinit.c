#include "metalc/crtinit.h"
#include "metalc/errno.h"
#include "metalc/internal/efi_shim.h"
#include "metalc/limits.h"
#include "metalc/locale.h"
#include "metalc/metalc.h"
#include "metalc/setjmp.h"
#include "metalc/stddef.h"


extern int malloc_init(void);
extern int malloc_teardown(void);
extern int stdio_init(void);
extern int stdio_teardown(void);
extern int locale_init(void);
extern int locale_teardown(void);


MetalCRuntimeInfo *__mcint_runtime_info __attribute__((visibility("hidden"))) = NULL;

__mcapi_jmp_buf __mcint_abort_target;


int cstdlib_init(MetalCRuntimeInfo *rti) {
    __mcint_runtime_info = rti;
    __mcapi_errno = 0;


    malloc_init();
    stdio_init();
    locale_init();
    setlocale(__mcapi_LC_ALL, "C");

    /* TODO (dargueta): Initialize atexit here. */

    rti->main_return_value = -1;
    rti->signal_code = -1;

    return 0;
}


static int cstdlib_teardown(void) {
    stdio_teardown();
    malloc_teardown();
    locale_teardown();
    return 0;
}


int cstdlib_run(int argc, char **argv, char **env) {
    int result;
    MetalCRuntimeInfo *rti = __mcint_runtime_info;

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

    cstdlib_teardown();
    return 0;
}


#if !METALC_COMPILE_FOR_TESTING
    #if METALC_PLATFORM_UEFI_FULL
        /* This is a UEFI application. */
        EFI_STATUS _start(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
            MetalCRuntimeInfo rti;

            rti.efi_image_handle = image_handle;
            rti.efi_system_table = system_table;

            cstdlib_init(&rti);
            return (EFI_STATUS)cstdlib_run(0, NULL, NULL);
        }
    #elif METALC_PLATFORM_UEFI_RUNTIME_ONLY
        /* UEFI runtime; this is the entry point for the kernel. */
        int _start(MetalCRuntimeInfo *rti) {
            /* TODO */
        }
    #else
        /* Bare metal; does not assume any underlying system but it *does* need some
         * information from the caller. */
        int _start(MetalCRuntimeInfo *rti) {
            rti.efi_image_handle = NULL;
            rti.efi_system_table = NULL;

            cstdlib_init(rti);
            cstdlib_run(0, NULL, NULL);
        }
    #endif
#endif
