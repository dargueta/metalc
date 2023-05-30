#include "metalc/errno.h"
#include "metalc/kernel_hooks.h"
#include "metalc/metalc.h"
#include "metalc/setjmp.h"
#include "metalc/signal.h"
#include "metalc/stdbool.h"
#include "metalc/stddef.h"


extern MetalCRuntimeInfo *mcinternal_runtime_info;
extern mclib_jmp_buf mcinternal_abort_target;


METALC_INTERNAL_ONLY
METALC_ATTR__NORETURN
static void sighandler_terminate(int sig) {
    switch (sig) {
        case mclib_SIGQUIT:
        case mclib_SIGILL:
        case mclib_SIGTRAP:
        case mclib_SIGABRT:
        case mclib_SIGBUS:
        case mclib_SIGFPE:
        case mclib_SIGSEGV:
        case mclib_SIGSTKFLT:
        case mclib_SIGXCPU:
        case mclib_SIGXFSZ:
        case mclib_SIGSYS:
            /* All of these signals require a core dump and immediate termination.
             * crt_teardown() will *not* be called and no resources are released.
             * It's up to the operating system to release memory, file handles,
             * etc. */
            krnlhook_core_dump(sig);
            break;

        default:
            longjmp(mcinternal_abort_target, sig);
            break;
    };
}


/* Signal handler does nothing. */
static void sighandler_ignore(int sig) {
    (void)sig;
}


/* Signal handler pauses the current process. */
static void sighandler_stop(int sig) {
    krnlhook_suspend(sig);
}


/* Signal handler resumes the current process. */
static void sighandler_resume(int sig) {
    krnlhook_resume(sig);
}


/*
static const signal_mask_t kDefaultMask = 0x04401aad00000004;
static signal_mask_t gCurrentSignalMask = kDefaultMask;

static signal_handler_t kHandlersByMaskValue[] = {
    sighandler_terminate,
    sighandler_ignore,
    sighandler_stop,
    sighandler_resume
};
*/


static const mclib_signal_handler_t default_signal_handlers[] = {
    /* Signal numbers begin at 1. Don't bother storing a handler for signal 0. */
    sighandler_terminate,   /* SIGHUP */
    sighandler_ignore,      /* SIGINT */
    sighandler_terminate,   /* SIGQUIT */
    sighandler_terminate,   /* SIGILL */
    sighandler_terminate,   /* SIGTRAP */
    sighandler_terminate,   /* SIGABRT, SIGIOT */
    sighandler_terminate,   /* SIGBUS */
    sighandler_terminate,   /* SIGFPE */
    sighandler_terminate,   /* SIGKILL */
    sighandler_terminate,   /* SIGUSR1 */
    sighandler_terminate,   /* SIGSEGV */
    sighandler_terminate,   /* SIGUSR2 */
    sighandler_terminate,   /* SIGPIPE */
    sighandler_terminate,   /* SIGALRM */
    sighandler_terminate,   /* SIGTERM */
    /* -------- END OF SIGNALS REQUIRED BY POSIX -------- */
    sighandler_terminate,   /* SIGSTKFLT */
    sighandler_ignore,      /* SIGCHLD */
    sighandler_resume,      /* SIGCONT */
    sighandler_stop,        /* SIGSTOP */
    sighandler_stop,        /* SIGTSTP */
    sighandler_stop,        /* SIGTTIN */
    sighandler_stop,        /* SIGTTOU */
    sighandler_ignore,      /* SIGURG */
    sighandler_terminate,   /* SIGXCPU */
    sighandler_terminate,   /* SIGXFSZ */
    sighandler_terminate,   /* SIGVTALRM */
    sighandler_terminate,   /* SIGPROF */
    sighandler_ignore,      /* SIGWINCH */
    sighandler_terminate,   /* SIGIO, SIGPOLL */
    sighandler_ignore,      /* SIGPWR */
    sighandler_terminate,   /* SIGSYS, SIGUNUSED */
};


static void sighandler_default(int sig) {
    default_signal_handlers[sig - 1](sig);
}


static mclib_signal_handler_t current_signal_handlers[] = {
    /* Signal numbers begin at 1. Don't bother storing a handler for signal 0. */
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default,
    sighandler_default
};


int raise(int sig) {
    if ((sig < 1) || (sig > 32))
        return mclib_EINVAL;

    current_signal_handlers[sig - 1](sig);
    return 0;
}
cstdlib_implement(raise);


mclib_signal_handler_t signal(int sig, mclib_signal_handler_t handler) {
    mclib_signal_handler_t original_handler;

    /* Ignore attempts to set signal handlers for signals that can't be overridden. */
    if ((sig == mclib_SIGTSTP) || (sig == mclib_SIGKILL)) {
        mclib_errno = mclib_EPERM;
        return sighandler_default;
    }
    /* Barf if the caller tries overriding a signal we don't support */
    else if ((sig < 1) || (sig > 32)) {
        mclib_errno = mclib_EINVAL;
        return sighandler_terminate;
    }

    original_handler = current_signal_handlers[sig - 1];

    if (handler == (mclib_signal_handler_t)mclib_SIG_DFL)
        current_signal_handlers[sig - 1] = sighandler_default;
    else if (handler == (mclib_signal_handler_t)mclib_SIG_IGN)
        current_signal_handlers[sig - 1] = sighandler_ignore;
    else if (handler == (mclib_signal_handler_t)mclib_SIG_ERR)
        current_signal_handlers[sig - 1] = sighandler_terminate;
    else
        current_signal_handlers[sig - 1] = handler;

    return original_handler;
}
cstdlib_implement(signal);
