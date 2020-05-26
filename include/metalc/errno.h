#ifndef INCLUDE_METALC_ERRNO_H_
#define INCLUDE_METALC_ERRNO_H_


extern int __mcapi_errno;


#define __mcapi_EPERM   1           /**< Operation not permitted. */
#define __mcapi_ENOENT  2           /**< No such file or directory. */
#define __mcapi_ESRCH   3           /**< No such process. */
#define __mcapi_EINTR   4           /**< Interrupted system call. */
#define __mcapi_EIO     5           /**< Input/output error. */
#define __mcapi_ENXIO   6           /**< No such device or address. */
#define __mcapi_E2BIG   7           /**< Argument list too long. */
#define __mcapi_ENOEXEC 8           /**< Exec format error. */
#define __mcapi_EBADF   9           /**< Bad file descriptor. */
#define __mcapi_ECHILD  10          /**< No child processes. */
#define __mcapi_EAGAIN  11          /**< Resource temporarily unavailable. */
#define __mcapi_EWOULDBLOCK 11      /**< Resource temporarily unavailable. */
#define __mcapi_ENOMEM  12          /**< Cannot allocate memory. */
#define __mcapi_EACCES  13          /**< Permission denied. */
#define __mcapi_EFAULT  14          /**< Bad address. */
#define __mcapi_ENOTBLK 15          /**< Block device required. */
#define __mcapi_EBUSY   16          /**< Device or resource busy. */
#define __mcapi_EEXIST  17          /**< File exists. */
#define __mcapi_EXDEV   18          /**< Invalid cross-device link. */
#define __mcapi_ENODEV  19          /**< No such device. */
#define __mcapi_ENOTDIR 20          /**< Not a directory. */
#define __mcapi_EISDIR  21          /**< Is a directory. */
#define __mcapi_EINVAL  22          /**< Invalid argument. */
#define __mcapi_ENFILE  23          /**< Too many open files in system. */
#define __mcapi_EMFILE  24          /**< Too many open files. */
#define __mcapi_ENOTTY  25          /**< Inappropriate ioctl for device. */
#define __mcapi_ETXTBSY 26          /**< Text file busy. */
#define __mcapi_EFBIG   27          /**< File too large. */
#define __mcapi_ENOSPC  28          /**< No space left on device. */
#define __mcapi_ESPIPE  29          /**< Illegal seek. */
#define __mcapi_EROFS   30          /**< Read-only file system. */
#define __mcapi_EMLINK  31          /**< Too many links. */
#define __mcapi_EPIPE   32          /**< Broken pipe. */
#define __mcapi_EDOM    33          /**< Numerical argument out of domain. */
#define __mcapi_ERANGE  34          /**< Numerical result out of range. */
#define __mcapi_EDEADLK 35          /**< Resource deadlock avoided. */
#define __mcapi_EDEADLOCK   35      /**< Resource deadlock avoided. */
#define __mcapi_ENAMETOOLONG    36  /**< File name too long. */
#define __mcapi_ENOLCK  37          /**< No locks available. */
#define __mcapi_ENOSYS  38          /**< Function not implemented. */
#define __mcapi_ENOTEMPTY   39      /**< Directory not empty. */
#define __mcapi_ELOOP       40      /**< Too many levels of symbolic links. */
/* 41 is missing */
#define __mcapi_ENOMSG  42          /**< No message of desired type. */
#define __mcapi_EIDRM   43          /**< Identifier removed. */
#define __mcapi_ECHRNG  44          /**< Channel number out of range. */
#define __mcapi_EL2NSYNC    45      /**< Level 2 not synchronized. */
#define __mcapi_EL3HLT  46          /**< Level 3 halted. */
#define __mcapi_EL3RST  47          /**< Level 3 reset. */
#define __mcapi_ELNRNG  48          /**< Link number out of range. */
#define __mcapi_EUNATCH 49          /**< Protocol driver not attached. */
#define __mcapi_ENOCSI  50          /**< No CSI structure available. */
#define __mcapi_EL2HLT  51          /**< Level 2 halted. */
#define __mcapi_EBADE   52          /**< Invalid exchange. */
#define __mcapi_EBADR   53          /**< Invalid request descriptor. */
#define __mcapi_EXFULL  54          /**< Exchange full. */
#define __mcapi_ENOANO  55          /**< No anode. */
#define __mcapi_EBADRQC 56          /**< Invalid request code. */
#define __mcapi_EBADSLT 57          /**< Invalid slot. */
#define __mcapi_EBFONT  59          /**< Bad font file format. */
#define __mcapi_ENOSTR  60          /**< Device not a stream. */
#define __mcapi_ENODATA 61          /**< No data available. */
#define __mcapi_ETIME   62          /**< Timer expired. */
#define __mcapi_ENOSR   63          /**< Out of streams resources. */
#define __mcapi_ENONET  64          /**< Machine is not on the network. */
#define __mcapi_ENOPKG  65          /**< Package not installed. */
#define __mcapi_EREMOTE 66          /**< Object is remote. */
#define __mcapi_ENOLINK 67          /**< Link has been severed. */
#define __mcapi_EADV    68          /**< Advertise error. */
#define __mcapi_ESRMNT  69          /**< Srmount error. */
#define __mcapi_ECOMM   70          /**< Communication error on send. */
#define __mcapi_EPROTO  71          /**< Protocol error. */
#define __mcapi_EMULTIHOP   72      /**< Multihop attempted. */
#define __mcapi_EDOTDOT     73      /**< RFS specific error. */
#define __mcapi_EBADMSG     74      /**< Bad message. */
#define __mcapi_EOVERFLOW   75      /**< Value too large for defined data type. */
#define __mcapi_ENOTUNIQ    76      /**< Name not unique on network. */
#define __mcapi_EBADFD      77      /**< File descriptor in bad state. */
#define __mcapi_EREMCHG     78      /**< Remote address changed. */
#define __mcapi_ELIBACC     79      /**< Cannot access a needed shared library. */
#define __mcapi_ELIBBAD     80      /**< Accessing a corrupted shared library. */
#define __mcapi_ELIBSCN     81      /**< .lib section in a.out corrupted. */
#define __mcapi_ELIBMAX     82      /**< Attempting to link in too many shared libraries. */
#define __mcapi_ELIBEXEC    83      /**< Cannot exec a shared library directly. */
#define __mcapi_EILSEQ      84      /**< Invalid or incomplete multibyte or wide character. */
#define __mcapi_ERESTART    85      /**< Interrupted system call should be restarted. */
#define __mcapi_ESTRPIPE    86      /**< Streams pipe error. */
#define __mcapi_EUSERS      87      /**< Too many users. */
#define __mcapi_ENOTSOCK    88      /**< Socket operation on non-socket. */
#define __mcapi_EDESTADDRREQ    89  /**< Destination address required. */
#define __mcapi_EMSGSIZE        90  /**< Message too long. */
#define __mcapi_EPROTOTYPE      91  /**< Protocol wrong type for socket. */
#define __mcapi_ENOPROTOOPT     92  /**< Protocol not available. */
#define __mcapi_EPROTONOSUPPORT 93  /**< Protocol not supported. */
#define __mcapi_ESOCKTNOSUPPORT 94  /**< Socket type not supported. */
#define __mcapi_ENOTSUP         95  /**< Operation not supported. */
#define __mcapi_EOPNOTSUPP      95  /**< Operation not supported. */
#define __mcapi_EPFNOSUPPORT    96  /**< Protocol family not supported. */
#define __mcapi_EAFNOSUPPORT    97  /**< Address family not supported by protocol. */
#define __mcapi_EADDRINUSE      98  /**< Address already in use. */
#define __mcapi_EADDRNOTAVAIL   99  /**< Cannot assign requested address. */
#define __mcapi_ENETDOWN        100 /**< Network is down. */
#define __mcapi_ENETUNREACH     101 /**< Network is unreachable. */
#define __mcapi_ENETRESET       102 /**< Network dropped connection on reset. */
#define __mcapi_ECONNABORTED    103 /**< Software caused connection abort. */
#define __mcapi_ECONNRESET      104 /**< Connection reset by peer. */
#define __mcapi_ENOBUFS     105     /**< No buffer space available. */
#define __mcapi_EISCONN     106     /**< Transport endpoint is already connected. */
#define __mcapi_ENOTCONN    107     /**< Transport endpoint is not connected. */
#define __mcapi_ESHUTDOWN   108     /**< Cannot send after transport endpoint shutdown. */
#define __mcapi_ETOOMANYREFS    109 /**< Too many references: cannot splice. */
#define __mcapi_ETIMEDOUT   110     /**< Connection timed out. */
#define __mcapi_ECONNREFUSED    111 /**< Connection refused. */
#define __mcapi_EHOSTDOWN   112     /**< Host is down. */
#define __mcapi_EHOSTUNREACH    113 /**< No route to host. */
#define __mcapi_EALREADY    114     /**< Operation already in progress. */
#define __mcapi_EINPROGRESS 115     /**< Operation now in progress. */
#define __mcapi_ESTALE      116     /**< Stale file handle. */
#define __mcapi_EUCLEAN     117     /**< Structure needs cleaning. */
#define __mcapi_ENOTNAM     118     /**< Not a XENIX named type file. */
#define __mcapi_ENAVAIL     119     /**< No XENIX semaphores available. */
#define __mcapi_EISNAM      120     /**< Is a named type file. */
#define __mcapi_EREMOTEIO   121     /**< Remote I/O error. */
#define __mcapi_EDQUOT      122     /**< Disk quota exceeded. */
#define __mcapi_ENOMEDIUM   123     /**< No medium found. */
#define __mcapi_EMEDIUMTYPE 124     /**< Wrong medium type. */
#define __mcapi_ECANCELED   125     /**< Operation canceled. */
#define __mcapi_ENOKEY      126     /**< Required key not available. */
#define __mcapi_EKEYEXPIRED 127     /**< Key has expired. */
#define __mcapi_EKEYREVOKED 128     /**< Key has been revoked. */
#define __mcapi_EKEYREJECTED    129 /**< Key was rejected by service. */
#define __mcapi_EOWNERDEAD  130     /**< Owner died. */
#define __mcapi_ENOTRECOVERABLE 131 /**< State not recoverable. */
#define __mcapi_ERFKILL     132     /**< Operation not possible due to RF-kill. */
#define __mcapi_EHWPOISON   133     /**< Memory page has hardware error. */

#define __mcapi__MAX_ERRNO  133

#include "bits/errno.h"

#endif  /* INCLUDE_METALC_ERRNO_H_ */
