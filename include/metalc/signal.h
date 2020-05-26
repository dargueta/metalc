#ifndef INCLUDE_METALC_SIGNAL_H_
#define INCLUDE_METALC_SIGNAL_H_

#include "crtinit.h"
#include "metalc.h"
#include "stdint.h"


typedef int32_t __mcapi_sig_atomic_t;
typedef int64_t __mcapi_signal_mask_t;
typedef void (*__mcapi_signal_handler_t)(int);

int raise(int sig);
__mcapi_signal_handler_t signal(int sig, __mcapi_signal_handler_t handler);

cstdlib_export(raise);
cstdlib_export(signal);


#define __mcapi_SIGHUP       1
#define __mcapi_SIGINT       2
#define __mcapi_SIGQUIT      3
#define __mcapi_SIGILL       4
#define __mcapi_SIGTRAP      5
#define __mcapi_SIGABRT      6
#define __mcapi_SIGIOT       __mcapi_SIGABRT
#define __mcapi_SIGBUS       7
#define __mcapi_SIGFPE       8
#define __mcapi_SIGKILL      9
#define __mcapi_SIGUSR1     10
#define __mcapi_SIGSEGV     11
#define __mcapi_SIGUSR2     12
#define __mcapi_SIGPIPE     13
#define __mcapi_SIGALRM     14
#define __mcapi_SIGTERM     15
#define __mcapi_SIGSTKFLT   16
#define __mcapi_SIGCHLD     17
#define __mcapi_SIGCONT     18
#define __mcapi_SIGSTOP     19
#define __mcapi_SIGTSTP     20
#define __mcapi_SIGTTIN     21
#define __mcapi_SIGTTOU     22
#define __mcapi_SIGURG      23
#define __mcapi_SIGXCPU     24
#define __mcapi_SIGXFSZ     25
#define __mcapi_SIGVTALRM   26
#define __mcapi_SIGPROF     27
#define __mcapi_SIGWINCH    28
#define __mcapi_SIGIO       29
#define __mcapi_SIGPOLL     __mcapi_SIGIO
/*
#define SIGLOST     29
*/
#define __mcapi_SIGPWR      30
#define __mcapi_SIGSYS      31
#define __mcapi_SIGUNUSED   31

/**
 * Default signal handling
 *
 * The signal is handled by the default action for that particular signal.
 */
#define __mcapi_SIG_DFL     0
#define __mcapi_SIG_IGN     1   /**< Ignore signal: The signal is ignored. */
#define __mcapi_SIG_ERR     2   /**< The signal triggers an error. */

#include "bits/signal.h"

#endif  /* INCLUDE_METALC_SIGNAL_H_ */
