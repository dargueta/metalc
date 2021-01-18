#include "metalc/errno.h"
#include "metalc/kernel_hooks.h"
#include "metalc/setjmp.h"
#include "metalc/signal.h"
#include "metalc/stdbool.h"
#include "metalc/stddef.h"


extern MetalCRuntimeInfo *__mcint_runtime_info;
extern jmp_buf __mcint_abort_target;


#if METALC_COMPILE_FOR_TESTING
    METALC_INTERNAL_WITH_ATTR(noreturn) extern void testhook_terminate(int sig);
    METALC_INTERNAL_WITH_ATTR(noreturn) extern void testhook_signal(int sig);
#endif


METALC_INTERNAL_WITH_ATTR(noreturn) static void _sighandler_term(int sig) {
    switch (sig) {
        case SIGQUIT:
        case SIGILL:
        case SIGTRAP:
        case SIGABRT:
        case SIGBUS:
        case SIGFPE:
        case SIGSEGV:
        case SIGSTKFLT:
        case SIGXCPU:
        case SIGXFSZ:
        case SIGSYS:
            /* All of these signals require a core dump and immediate termination.
             * crt_teardown() will *not* be called and no resources are released.
             * It's up to the operating system to release memory, file handles,
             * etc. */
            #if METALC_COMPILE_FOR_TESTING
                testhook_terminate(sig);
            #else
                krnlhook_core_dump(sig, __mcint_runtime_info->udata);
            #endif
            break;

        default:
            #if METALC_COMPILE_FOR_TESTING
                testhook_terminate(sig);
            #else
                longjmp(__mcint_abort_target, sig);
            #endif
            break;
    };
}


/* Signal handler does nothing. */
static void _sighandler_ignore(int sig) {
    (void)sig;
}


/* Signal handler pauses the current process. */
static void _sighandler_stop(int sig) {
    #if METALC_COMPILE_FOR_TESTING
        testhook_signal(sig);
    #else
        krnlhook_suspend(sig, __mcint_runtime_info->udata);
    #endif
}


/* Signal handler resumes the current process. */
static void _sighandler_resume(int sig) {
    #if METALC_COMPILE_FOR_TESTING
        testhook_signal(sig);
    #else
        krnlhook_resume(sig, __mcint_runtime_info->udata);
    #endif
}


/*
static const signal_mask_t kDefaultMask = 0x04401aad00000004;
static signal_mask_t gCurrentSignalMask = kDefaultMask;

static signal_handler_t kHandlersByMaskValue[] = {
    _sighandler_term,
    _sighandler_ignore,
    _sighandler_stop,
    _sighandler_resume
};
*/


static const signal_handler_t _default_signal_handlers[] = {
    /* Signal numbers begin at 1. Don't bother storing a handler for signal 0. */
    _sighandler_term,       /* SIGHUP */
    _sighandler_ignore,     /* SIGINT */
    _sighandler_term,       /* SIGQUIT */
    _sighandler_term,       /* SIGILL */
    _sighandler_term,       /* SIGTRAP */
    _sighandler_term,       /* SIGABRT, SIGIOT */
    _sighandler_term,       /* SIGBUS */
    _sighandler_term,       /* SIGFPE */
    _sighandler_term,       /* SIGKILL */
    _sighandler_term,       /* SIGUSR1 */
    _sighandler_term,       /* SIGSEGV */
    _sighandler_term,       /* SIGUSR2 */
    _sighandler_term,       /* SIGPIPE */
    _sighandler_term,       /* SIGALRM */
    _sighandler_term,       /* SIGTERM */
    /* -------- END OF SIGNALS REQUIRED BY POSIX -------- */
    _sighandler_term,       /* SIGSTKFLT */
    _sighandler_ignore,     /* SIGCHLD */
    _sighandler_resume,     /* SIGCONT */
    _sighandler_stop,       /* SIGSTOP */
    _sighandler_stop,       /* SIGTSTP */
    _sighandler_stop,       /* SIGTTIN */
    _sighandler_stop,       /* SIGTTOU */
    _sighandler_ignore,     /* SIGURG */
    _sighandler_term,       /* SIGXCPU */
    _sighandler_term,       /* SIGXFSZ */
    _sighandler_term,       /* SIGVTALRM */
    _sighandler_term,       /* SIGPROF */
    _sighandler_ignore,     /* SIGWINCH */
    _sighandler_term,       /* SIGIO, SIGPOLL */
    _sighandler_ignore,     /* SIGPWR */
    _sighandler_term,       /* SIGSYS, SIGUNUSED */
};


static void _sighandler_default(int sig) {
    _default_signal_handlers[sig - 1](sig);
}


static signal_handler_t _current_signal_handlers[] = {
    /* Signal numbers begin at 1. Don't bother storing a handler for signal 0. */
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default,
    _sighandler_default
};


int raise(int sig) {
    if ((sig < 1) || (sig > 32))
        return EINVAL;

    _current_signal_handlers[sig - 1](sig);
    return 0;
}


signal_handler_t signal(int sig, signal_handler_t handler) {
    signal_handler_t original_handler;

    /* Ignore attempts to set signal handlers for signals that can't be overridden. */
    if ((sig == SIGTSTP) || (sig == SIGKILL)) {
        errno = EPERM;
        return _sighandler_default;
    }
    /* Barf if the caller tries overriding a signal we don't support */
    else if ((sig < 1) || (sig > 32)) {
        errno = EINVAL;
        return _sighandler_term;
    }

    original_handler = _current_signal_handlers[sig - 1];

    if (handler == (signal_handler_t)SIG_DFL)
        _current_signal_handlers[sig - 1] = _sighandler_default;
    else if (handler == (signal_handler_t)SIG_IGN)
        _current_signal_handlers[sig - 1] = _sighandler_ignore;
    else if (handler == (signal_handler_t)SIG_ERR)
        _current_signal_handlers[sig - 1] = _sighandler_term;
    else
        _current_signal_handlers[sig - 1] = handler;

    return original_handler;
}
