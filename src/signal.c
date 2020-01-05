#include <metalc/errno.h>
#include <metalc/kernel_hooks.h>
#include <metalc/setjmp.h>
#include <metalc/signal.h>
#include <metalc/stdbool.h>
#include <metalc/stddef.h>


extern MetalCRuntimeInfo *__mclib_runtime_info;
extern __mcapi_jmp_buf __mclib_abort_target;


__attribute__((noreturn)) static void _sighandler_term(int sig) {
    switch (sig) {
        case __mcapi_SIGQUIT:
        case __mcapi_SIGILL:
        case __mcapi_SIGTRAP:
        case __mcapi_SIGABRT:
        case __mcapi_SIGBUS:
        case __mcapi_SIGFPE:
        case __mcapi_SIGSEGV:
        case __mcapi_SIGSTKFLT:
        case __mcapi_SIGXCPU:
        case __mcapi_SIGXFSZ:
        case __mcapi_SIGSYS:
            /* All of these signals require a core dump and immediate termination.
             * crt_teardown() will *not* be called and no resources are released.
             * It's up to the operating system to release memory, file handles,
             * etc. */
            krnlhook_core_dump(sig, __mclib_runtime_info->udata);
            break;

        default:
            __mcapi_longjmp(__mclib_abort_target, sig);
            break;
    };
}


/* Signal handler does nothing. */
static void _sighandler_ignore(int sig) {
    (void)sig;
}


/* Signal handler pauses the current process. */
static void _sighandler_stop(int sig) {
    krnlhook_suspend(sig, __mclib_runtime_info->udata);
}


/* Signal handler resumes the current process. */
static void _sighandler_resume(int sig) {
    krnlhook_resume(sig, __mclib_runtime_info->udata);
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


static const __mcapi_signal_handler_t gDefaultSignalHandlers[] = {
    /* Signal numbers begin at 1. Don't bother storing a handler for signal 0. */
    _sighandler_term,       /* __mcapi_SIGHUP */
    _sighandler_ignore,     /* __mcapi_SIGINT */
    _sighandler_term,       /* __mcapi_SIGQUIT */
    _sighandler_term,       /* __mcapi_SIGILL */
    _sighandler_term,       /* __mcapi_SIGTRAP */
    _sighandler_term,       /* __mcapi_SIGABRT, __mcapi_SIGIOT */
    _sighandler_term,       /* __mcapi_SIGBUS */
    _sighandler_term,       /* __mcapi_SIGFPE */
    _sighandler_term,       /* __mcapi_SIGKILL */
    _sighandler_term,       /* __mcapi_SIGUSR1 */
    _sighandler_term,       /* __mcapi_SIGSEGV */
    _sighandler_term,       /* __mcapi_SIGUSR2 */
    _sighandler_term,       /* __mcapi_SIGPIPE */
    _sighandler_term,       /* __mcapi_SIGALRM */
    _sighandler_term,       /* __mcapi_SIGTERM */
    /* -------- END OF __mcapi_SIGNALS REQUIRED BY POSIX -------- */
    _sighandler_term,       /* __mcapi_SIGSTKFLT */
    _sighandler_ignore,     /* __mcapi_SIGCHLD */
    _sighandler_resume,     /* __mcapi_SIGCONT */
    _sighandler_stop,       /* __mcapi_SIGSTOP */
    _sighandler_stop,       /* __mcapi_SIGTSTP */
    _sighandler_stop,       /* __mcapi_SIGTTIN */
    _sighandler_stop,       /* __mcapi_SIGTTOU */
    _sighandler_ignore,     /* __mcapi_SIGURG */
    _sighandler_term,       /* __mcapi_SIGXCPU */
    _sighandler_term,       /* __mcapi_SIGXFSZ */
    _sighandler_term,       /* __mcapi_SIGVTALRM */
    _sighandler_term,       /* __mcapi_SIGPROF */
    _sighandler_ignore,     /* __mcapi_SIGWINCH */
    _sighandler_term,       /* __mcapi_SIGIO, __mcapi_SIGPOLL */
    _sighandler_ignore,     /* __mcapi_SIGPWR */
    _sighandler_term,       /* __mcapi_SIGSYS, __mcapi_SIGUNUSED */
};


static void _sighandler_default(int sig) {
    gDefaultSignalHandlers[sig - 1](sig);
}


static __mcapi_signal_handler_t gConfiguredSignalHandlers[] = {
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


METALC_API_EXPORT int __mcapi_raise(int sig) {
    if ((sig < 1) || (sig > 32))
        return __mcapi_EINVAL;

    gConfiguredSignalHandlers[sig - 1](sig);
    return 0;
}


METALC_API_EXPORT __mcapi_signal_handler_t __mcapi_signal(int sig, __mcapi_signal_handler_t handler) {
    __mcapi_signal_handler_t original_handler;

    /* Ignore attempts to set signal handlers for signals that can't be overridden. */
    if ((sig == __mcapi_SIGTSTP) || (sig == __mcapi_SIGKILL)) {
        __mcapi_errno = __mcapi_EPERM;
        return _sighandler_default;
    }
    /* Barf if the caller tries overriding a signal we don't support */
    else if ((sig < 1) || (sig > 32)) {
        __mcapi_errno = __mcapi_EINVAL;
        return _sighandler_term;
    }

    original_handler = gConfiguredSignalHandlers[sig - 1];

    if (handler == (__mcapi_signal_handler_t)__mcapi_SIG_DFL)
        gConfiguredSignalHandlers[sig - 1] = _sighandler_default;
    else if (handler == (__mcapi_signal_handler_t)__mcapi_SIG_IGN)
        gConfiguredSignalHandlers[sig - 1] = _sighandler_ignore;
    else if (handler == (__mcapi_signal_handler_t)__mcapi_SIG_ERR)
        gConfiguredSignalHandlers[sig - 1] = _sighandler_term;
    else
        gConfiguredSignalHandlers[sig - 1] = handler;

    return original_handler;
}
