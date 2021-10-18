#ifndef INCLUDE_METALC_ERRNO_H_
#define INCLUDE_METALC_ERRNO_H_


extern int mclib_errno;


#define mclib_EPERM   1           /**< Operation not permitted. */
#define mclib_ENOENT  2           /**< No such file or directory. */
#define mclib_ESRCH   3           /**< No such process. */
#define mclib_EINTR   4           /**< Interrupted system call. */
#define mclib_EIO     5           /**< Input/output error. */
#define mclib_ENXIO   6           /**< No such device or address. */
#define mclib_E2BIG   7           /**< Argument list too long. */
#define mclib_ENOEXEC 8           /**< Exec format error. */
#define mclib_EBADF   9           /**< Bad file descriptor. */
#define mclib_ECHILD  10          /**< No child processes. */
#define mclib_EAGAIN  11          /**< Resource temporarily unavailable. */
#define mclib_EWOULDBLOCK 11      /**< Resource temporarily unavailable. */
#define mclib_ENOMEM  12          /**< Cannot allocate memory. */
#define mclib_EACCES  13          /**< Permission denied. */
#define mclib_EFAULT  14          /**< Bad address. */
#define mclib_ENOTBLK 15          /**< Block device required. */
#define mclib_EBUSY   16          /**< Device or resource busy. */
#define mclib_EEXIST  17          /**< File exists. */
#define mclib_EXDEV   18          /**< Invalid cross-device link. */
#define mclib_ENODEV  19          /**< No such device. */
#define mclib_ENOTDIR 20          /**< Not a directory. */
#define mclib_EISDIR  21          /**< Is a directory. */
#define mclib_EINVAL  22          /**< Invalid argument. */
#define mclib_ENFILE  23          /**< Too many open files in system. */
#define mclib_EMFILE  24          /**< Too many open files. */
#define mclib_ENOTTY  25          /**< Inappropriate ioctl for device. */
#define mclib_ETXTBSY 26          /**< Text file busy. */
#define mclib_EFBIG   27          /**< File too large. */
#define mclib_ENOSPC  28          /**< No space left on device. */
#define mclib_ESPIPE  29          /**< Illegal seek. */
#define mclib_EROFS   30          /**< Read-only file system. */
#define mclib_EMLINK  31          /**< Too many links. */
#define mclib_EPIPE   32          /**< Broken pipe. */
#define mclib_EDOM    33          /**< Numerical argument out of domain. */
#define mclib_ERANGE  34          /**< Numerical result out of range. */
#define mclib_EDEADLK 35          /**< Resource deadlock avoided. */
#define mclib_EDEADLOCK   35      /**< Resource deadlock avoided. */
#define mclib_ENAMETOOLONG    36  /**< File name too long. */
#define mclib_ENOLCK  37          /**< No locks available. */
#define mclib_ENOSYS  38          /**< Function not implemented. */
#define mclib_ENOTEMPTY   39      /**< Directory not empty. */
#define mclib_ELOOP       40      /**< Too many levels of symbolic links. */
/* 41 is missing */
#define mclib_ENOMSG  42          /**< No message of desired type. */
#define mclib_EIDRM   43          /**< Identifier removed. */
#define mclib_ECHRNG  44          /**< Channel number out of range. */
#define mclib_EL2NSYNC    45      /**< Level 2 not synchronized. */
#define mclib_EL3HLT  46          /**< Level 3 halted. */
#define mclib_EL3RST  47          /**< Level 3 reset. */
#define mclib_ELNRNG  48          /**< Link number out of range. */
#define mclib_EUNATCH 49          /**< Protocol driver not attached. */
#define mclib_ENOCSI  50          /**< No CSI structure available. */
#define mclib_EL2HLT  51          /**< Level 2 halted. */
#define mclib_EBADE   52          /**< Invalid exchange. */
#define mclib_EBADR   53          /**< Invalid request descriptor. */
#define mclib_EXFULL  54          /**< Exchange full. */
#define mclib_ENOANO  55          /**< No anode. */
#define mclib_EBADRQC 56          /**< Invalid request code. */
#define mclib_EBADSLT 57          /**< Invalid slot. */
#define mclib_EBFONT  59          /**< Bad font file format. */
#define mclib_ENOSTR  60          /**< Device not a stream. */
#define mclib_ENODATA 61          /**< No data available. */
#define mclib_ETIME   62          /**< Timer expired. */
#define mclib_ENOSR   63          /**< Out of streams resources. */
#define mclib_ENONET  64          /**< Machine is not on the network. */
#define mclib_ENOPKG  65          /**< Package not installed. */
#define mclib_EREMOTE 66          /**< Object is remote. */
#define mclib_ENOLINK 67          /**< Link has been severed. */
#define mclib_EADV    68          /**< Advertise error. */
#define mclib_ESRMNT  69          /**< Srmount error. */
#define mclib_ECOMM   70          /**< Communication error on send. */
#define mclib_EPROTO  71          /**< Protocol error. */
#define mclib_EMULTIHOP   72      /**< Multihop attempted. */
#define mclib_EDOTDOT     73      /**< RFS specific error. */
#define mclib_EBADMSG     74      /**< Bad message. */
#define mclib_EOVERFLOW   75      /**< Value too large for defined data type. */
#define mclib_ENOTUNIQ    76      /**< Name not unique on network. */
#define mclib_EBADFD      77      /**< File descriptor in bad state. */
#define mclib_EREMCHG     78      /**< Remote address changed. */
#define mclib_ELIBACC     79      /**< Cannot access a needed shared library. */
#define mclib_ELIBBAD     80      /**< Accessing a corrupted shared library. */
#define mclib_ELIBSCN     81      /**< .lib section in a.out corrupted. */
#define mclib_ELIBMAX     82      /**< Attempting to link in too many shared libraries. */
#define mclib_ELIBEXEC    83      /**< Cannot exec a shared library directly. */
#define mclib_EILSEQ      84      /**< Invalid or incomplete multibyte or wide character. */
#define mclib_ERESTART    85      /**< Interrupted system call should be restarted. */
#define mclib_ESTRPIPE    86      /**< Streams pipe error. */
#define mclib_EUSERS      87      /**< Too many users. */
#define mclib_ENOTSOCK    88      /**< Socket operation on non-socket. */
#define mclib_EDESTADDRREQ    89  /**< Destination address required. */
#define mclib_EMSGSIZE        90  /**< Message too long. */
#define mclib_EPROTOTYPE      91  /**< Protocol wrong type for socket. */
#define mclib_ENOPROTOOPT     92  /**< Protocol not available. */
#define mclib_EPROTONOSUPPORT 93  /**< Protocol not supported. */
#define mclib_ESOCKTNOSUPPORT 94  /**< Socket type not supported. */
#define mclib_ENOTSUP         95  /**< Operation not supported. */
#define mclib_EOPNOTSUPP      95  /**< Operation not supported. */
#define mclib_EPFNOSUPPORT    96  /**< Protocol family not supported. */
#define mclib_EAFNOSUPPORT    97  /**< Address family not supported by protocol. */
#define mclib_EADDRINUSE      98  /**< Address already in use. */
#define mclib_EADDRNOTAVAIL   99  /**< Cannot assign requested address. */
#define mclib_ENETDOWN        100 /**< Network is down. */
#define mclib_ENETUNREACH     101 /**< Network is unreachable. */
#define mclib_ENETRESET       102 /**< Network dropped connection on reset. */
#define mclib_ECONNABORTED    103 /**< Software caused connection abort. */
#define mclib_ECONNRESET      104 /**< Connection reset by peer. */
#define mclib_ENOBUFS     105     /**< No buffer space available. */
#define mclib_EISCONN     106     /**< Transport endpoint is already connected. */
#define mclib_ENOTCONN    107     /**< Transport endpoint is not connected. */
#define mclib_ESHUTDOWN   108     /**< Cannot send after transport endpoint shutdown. */
#define mclib_ETOOMANYREFS    109 /**< Too many references: cannot splice. */
#define mclib_ETIMEDOUT   110     /**< Connection timed out. */
#define mclib_ECONNREFUSED    111 /**< Connection refused. */
#define mclib_EHOSTDOWN   112     /**< Host is down. */
#define mclib_EHOSTUNREACH    113 /**< No route to host. */
#define mclib_EALREADY    114     /**< Operation already in progress. */
#define mclib_EINPROGRESS 115     /**< Operation now in progress. */
#define mclib_ESTALE      116     /**< Stale file handle. */
#define mclib_EUCLEAN     117     /**< Structure needs cleaning. */
#define mclib_ENOTNAM     118     /**< Not a XENIX named type file. */
#define mclib_ENAVAIL     119     /**< No XENIX semaphores available. */
#define mclib_EISNAM      120     /**< Is a named type file. */
#define mclib_EREMOTEIO   121     /**< Remote I/O error. */
#define mclib_EDQUOT      122     /**< Disk quota exceeded. */
#define mclib_ENOMEDIUM   123     /**< No medium found. */
#define mclib_EMEDIUMTYPE 124     /**< Wrong medium type. */
#define mclib_ECANCELED   125     /**< Operation canceled. */
#define mclib_ENOKEY      126     /**< Required key not available. */
#define mclib_EKEYEXPIRED 127     /**< Key has expired. */
#define mclib_EKEYREVOKED 128     /**< Key has been revoked. */
#define mclib_EKEYREJECTED    129 /**< Key was rejected by service. */
#define mclib_EOWNERDEAD  130     /**< Owner died. */
#define mclib_ENOTRECOVERABLE 131 /**< State not recoverable. */
#define mclib_ERFKILL     132     /**< Operation not possible due to RF-kill. */
#define mclib_EHWPOISON   133     /**< Memory page has hardware error. */

#define mclib__MAX_ERRNO  133

#include "bits/errno.h"

#endif  /* INCLUDE_METALC_ERRNO_H_ */
