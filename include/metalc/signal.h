#ifndef INCLUDE_METALC_SIGNAL_H_
#define INCLUDE_METALC_SIGNAL_H_

#include "crtinit.h"
#include "metalc.h"
#include "stdint.h"


typedef int32_t mclib_sig_atomic_t;
typedef int64_t mclib_signal_mask_t;
typedef void (*mclib_signal_handler_t)(int);

int raise(int sig);
mclib_signal_handler_t signal(int sig, mclib_signal_handler_t handler);

cstdlib_export(raise);
cstdlib_export(signal);


#define mclib_SIGHUP       1
#define mclib_SIGINT       2
#define mclib_SIGQUIT      3
#define mclib_SIGILL       4
#define mclib_SIGTRAP      5
#define mclib_SIGABRT      6
#define mclib_SIGIOT       mclib_SIGABRT
#define mclib_SIGBUS       7
#define mclib_SIGFPE       8
#define mclib_SIGKILL      9
#define mclib_SIGUSR1     10
#define mclib_SIGSEGV     11
#define mclib_SIGUSR2     12
#define mclib_SIGPIPE     13
#define mclib_SIGALRM     14
#define mclib_SIGTERM     15
#define mclib_SIGSTKFLT   16
#define mclib_SIGCHLD     17
#define mclib_SIGCONT     18
#define mclib_SIGSTOP     19
#define mclib_SIGTSTP     20
#define mclib_SIGTTIN     21
#define mclib_SIGTTOU     22
#define mclib_SIGURG      23
#define mclib_SIGXCPU     24
#define mclib_SIGXFSZ     25
#define mclib_SIGVTALRM   26
#define mclib_SIGPROF     27
#define mclib_SIGWINCH    28
#define mclib_SIGIO       29
#define mclib_SIGPOLL     mclib_SIGIO
/*
#define SIGLOST     29
*/
#define mclib_SIGPWR      30
#define mclib_SIGSYS      31
#define mclib_SIGUNUSED   31

/**
 * Default signal handling
 *
 * The signal is handled by the default action for that particular signal.
 */
#define mclib_SIG_DFL     0
#define mclib_SIG_IGN     1   /**< Ignore signal: The signal is ignored. */
#define mclib_SIG_ERR     2   /**< The signal triggers an error. */

#endif  /* INCLUDE_METALC_SIGNAL_H_ */
