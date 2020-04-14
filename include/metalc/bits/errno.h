/**
 * Define the real C standard errno values if we're not testing against the host.
 *
 * @file errno.h
 */

#ifndef INCLUDE_METALC_BITS_ERRNO_H_

#if !defined METALC_DISABLE_STDLIB_DEFS
    #define EPERM   __mcapi_EPERM
    #define ENOENT  __mcapi_ENOENT
    #define ESRCH   __mcapi_ESRCH
    #define EINTR   __mcapi_EINTR
    #define EIO     __mcapi_EIO
    #define ENXIO   __mcapi_ENXIO
    #define E2BIG   __mcapi_E2BIG
    #define ENOEXEC __mcapi_ENOEXEC
    #define EBADF   __mcapi_EBADF
    #define ECHILD  __mcapi_ECHILD
    #define EAGAIN  __mcapi_EAGAIN
    #define EWOULDBLOCK __mcapi_EWOULDBLOCK
    #define ENOMEM  __mcapi_ENOMEM
    #define EACCES  __mcapi_EACCES
    #define EFAULT  __mcapi_EFAULT
    #define ENOTBLK __mcapi_ENOTBLK
    #define EBUSY   __mcapi_EBUSY
    #define EEXIST  __mcapi_EEXIST
    #define EXDEV   __mcapi_EXDEV
    #define ENODEV  __mcapi_ENODEV
    #define ENOTDIR __mcapi_ENOTDIR
    #define EISDIR  __mcapi_EISDIR
    #define EINVAL  __mcapi_EINVAL
    #define ENFILE  __mcapi_ENFILE
    #define EMFILE  __mcapi_EMFILE
    #define ENOTTY  __mcapi_ENOTTY
    #define ETXTBSY __mcapi_ETXTBSY
    #define EFBIG   __mcapi_EFBIG
    #define ENOSPC  __mcapi_ENOSPC
    #define ESPIPE  __mcapi_ESPIPE
    #define EROFS   __mcapi_EROFS
    #define EMLINK  __mcapi_EMLINK
    #define EPIPE   __mcapi_EPIPE
    #define EDOM    __mcapi_EDOM
    #define ERANGE  __mcapi_ERANGE
    #define EDEADLK __mcapi_EDEADLK
    #define EDEADLOCK       __mcapi_EDEADLOCK
    #define ENAMETOOLONG    __mcapi_ENAMETOOLONG
    #define ENOLCK      __mcapi_ENOLCK
    #define ENOSYS      __mcapi_ENOSYS
    #define ENOTEMPTY   __mcapi_ENOTEMPTY
    #define ELOOP   __mcapi_ELOOP
    #define ENOMSG  __mcapi_ENOMSG
    #define EIDRM   __mcapi_EIDRM
    #define ECHRNG  __mcapi_ECHRNG
    #define EL2NSYNC    __mcapi_EL2NSYNC
    #define EL3HLT  __mcapi_EL3HLT
    #define EL3RST  __mcapi_EL3RST
    #define ELNRNG  __mcapi_ELNRNG
    #define EUNATCH __mcapi_EUNATCH
    #define ENOCSI  __mcapi_ENOCSI
    #define EL2HLT  __mcapi_EL2HLT
    #define EBADE   __mcapi_EBADE
    #define EBADR   __mcapi_EBADR
    #define EXFULL  __mcapi_EXFULL
    #define ENOANO  __mcapi_ENOANO
    #define EBADRQC __mcapi_EBADRQC
    #define EBADSLT __mcapi_EBADSLT
    #define EBFONT  __mcapi_EBFONT
    #define ENOSTR  __mcapi_ENOSTR
    #define ENODATA __mcapi_ENODATA
    #define ETIME   __mcapi_ETIME
    #define ENOSR   __mcapi_ENOSR
    #define ENONET  __mcapi_ENONET
    #define ENOPKG  __mcapi_ENOPKG
    #define EREMOTE __mcapi_EREMOTE
    #define ENOLINK __mcapi_ENOLINK
    #define EADV    __mcapi_EADV
    #define ESRMNT  __mcapi_ESRMNT
    #define ECOMM   __mcapi_ECOMM
    #define EPROTO  __mcapi_EPROTO
    #define EMULTIHOP   __mcapi_EMULTIHOP
    #define EDOTDOT     __mcapi_EDOTDOT
    #define EBADMSG     __mcapi_EBADMSG
    #define EOVERFLOW   __mcapi_EOVERFLOW
    #define ENOTUNIQ    __mcapi_ENOTUNIQ
    #define EBADFD  __mcapi_EBADFD
    #define EREMCHG __mcapi_EREMCHG
    #define ELIBACC __mcapi_ELIBACC
    #define ELIBBAD __mcapi_ELIBBAD
    #define ELIBSCN __mcapi_ELIBSCN
    #define ELIBMAX __mcapi_ELIBMAX
    #define ELIBEXEC    __mcapi_ELIBEXEC
    #define EILSEQ      __mcapi_EILSEQ
    #define ERESTART    __mcapi_ERESTART
    #define ESTRPIPE    __mcapi_ESTRPIPE
    #define EUSERS      __mcapi_EUSERS
    #define ENOTSOCK    __mcapi_ENOTSOCK
    #define EDESTADDRREQ    __mcapi_EDESTADDRREQ
    #define EMSGSIZE    __mcapi_EMSGSIZE
    #define EPROTOTYPE  __mcapi_EPROTOTYPE
    #define ENOPROTOOPT __mcapi_ENOPROTOOPT
    #define EPROTONOSUPPORT __mcapi_EPROTONOSUPPORT
    #define ESOCKTNOSUPPORT __mcapi_ESOCKTNOSUPPORT
    #define ENOTSUP     __mcapi_ENOTSUP
    #define EOPNOTSUPP  __mcapi_EOPNOTSUPP
    #define EPFNOSUPPORT    __mcapi_EPFNOSUPPORT
    #define EAFNOSUPPORT    __mcapi_EAFNOSUPPORT
    #define EADDRINUSE  __mcapi_EADDRINUSE
    #define EADDRNOTAVAIL   __mcapi_EADDRNOTAVAIL
    #define ENETDOWN    __mcapi_ENETDOWN
    #define ENETUNREACH __mcapi_ENETUNREACH
    #define ENETRESET   __mcapi_ENETRESET
    #define ECONNABORTED    __mcapi_ECONNABORTED
    #define ECONNRESET  __mcapi_ECONNRESET
    #define ENOBUFS __mcapi_ENOBUFS
    #define EISCONN __mcapi_EISCONN
    #define ENOTCONN    __mcapi_ENOTCONN
    #define ESHUTDOWN   __mcapi_ESHUTDOWN
    #define ETOOMANYREFS    __mcapi_ETOOMANYREFS
    #define ETIMEDOUT   __mcapi_ETIMEDOUT
    #define ECONNREFUSED    __mcapi_ECONNREFUSED
    #define EHOSTDOWN   __mcapi_EHOSTDOWN
    #define EHOSTUNREACH    __mcapi_EHOSTUNREACH
    #define EALREADY    __mcapi_EALREADY
    #define EINPROGRESS __mcapi_EINPROGRESS
    #define ESTALE  __mcapi_ESTALE
    #define EUCLEAN __mcapi_EUCLEAN
    #define ENOTNAM __mcapi_ENOTNAM
    #define ENAVAIL __mcapi_ENAVAIL
    #define EISNAM  __mcapi_EISNAM
    #define EREMOTEIO   __mcapi_EREMOTEIO
    #define EDQUOT  __mcapi_EDQUOT
    #define ENOMEDIUM   __mcapi_ENOMEDIUM
    #define EMEDIUMTYPE __mcapi_EMEDIUMTYPE
    #define ECANCELED   __mcapi_ECANCELED
    #define ENOKEY  __mcapi_ENOKEY
    #define EKEYEXPIRED __mcapi_EKEYEXPIRED
    #define EKEYREVOKED __mcapi_EKEYREVOKED
    #define EKEYREJECTED    __mcapi_EKEYREJECTED
    #define EOWNERDEAD  __mcapi_EOWNERDEAD
    #define ENOTRECOVERABLE __mcapi_ENOTRECOVERABLE
    #define ERFKILL __mcapi_ERFKILL
    #define EHWPOISON   __mcapi_EHWPOISON
#endif /* METALC_DISABLE_STDLIB_DEFS */
#endif /* INCLUDE_METALC_BITS_ERRNO_H_ */
