#ifndef INCLUDE_METALC_SIGNAL_H_
#define INCLUDE_METALC_SIGNAL_H_

#include <metalc/crtinit.h>
#include <metalc/metalc.h>
#include <metalc/stdint.h>


typedef int32_t sig_atomic_t;
typedef int64_t signal_mask_t;
typedef void (*signal_handler_t)(int);

METALC_API_EXPORT int raise(int sig);
METALC_API_EXPORT signal_handler_t signal(int sig, signal_handler_t handler);

#define SIGHUP       1
#define SIGINT       2
#define SIGQUIT      3
#define SIGILL       4
#define SIGTRAP      5
#define SIGABRT      6
#define SIGIOT       SIGABRT
#define SIGBUS       7
#define SIGFPE       8
#define SIGKILL      9
#define SIGUSR1     10
#define SIGSEGV     11
#define SIGUSR2     12
#define SIGPIPE     13
#define SIGALRM     14
#define SIGTERM     15
#define SIGSTKFLT   16
#define SIGCHLD     17
#define SIGCONT     18
#define SIGSTOP     19
#define SIGTSTP     20
#define SIGTTIN     21
#define SIGTTOU     22
#define SIGURG      23
#define SIGXCPU     24
#define SIGXFSZ     25
#define SIGVTALRM   26
#define SIGPROF     27
#define SIGWINCH    28
#define SIGIO       29
#define SIGPOLL     SIGIO
/*
#define SIGLOST     29
*/
#define SIGPWR      30
#define SIGSYS      31
#define SIGUNUSED   31

/**
 * Default signal handling
 *
 * The signal is handled by the default action for that particular signal.
 */
#define SIG_DFL     0
#define SIG_IGN     1   /**< Ignore signal: The signal is ignored. */
#define SIG_ERR     2   /**< The signal triggers an error. */

#endif  /* INCLUDE_METALC_SIGNAL_H_ */
