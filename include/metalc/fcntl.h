#ifndef INCLUDE_METALC_FCNTL_H_
#define INCLUDE_METALC_FCNTL_H_

/* File access modes */
#define O_RDONLY    0   /**< Open read-only. */
#define O_WRONLY    1   /**< Open write-only. */
#define O_RDWR      2   /**< Open read/write. */


/* Bit flags for controlling I/O operations on the file. */
#define O_SHLOCK    0x00000010  /**< Open with shared file lock. */
#define O_EXLOCK    0x00000020  /**< Open with shared exclusive lock. */
#define O_ASYNC     0x00000040  /**< Send SIGIO to owner when data is ready. */
#define O_FSYNC     0x00000080  /**< Synchronous writes. */
#define O_NOFOLLOW  0x00000100  /**< Do not follow links. */
#define O_CREAT     0x00000200  /**< Create file if it doesn't exist. */
#define O_TRUNC     0x00000400  /**< Truncate file to zero length. */
#define O_EXCL      0x00000800  /**< Fail if file already exists. */
#define O_NOCTTY    0x00008000  /**< Don't assign a controlling terminal. */
#define O_SYNC      O_FSYNC     /**< Same as @ref O_SYNC. */
#define O_DSYNC     0x00010000  /**< Synchronize data. */
#define O_RSYNC     0x00020000  /**< Synchronize read operations. */
#define O_DIRECTORY 0x00200000  /**< Must be a directory. */
#define O_CLOEXEC   0x00400000  /**< Set close_on_exec. */
#define O_LARGEFILE 0

/* File status flags */
#define O_NONBLOCK  0x0004      /**< Non-blocking I/O. */
#define O_NDELAY    O_NONBLOCK  /**< Same as @ref O_NONBLOCK */
#define O_APPEND    0x0008      /**< Writes append to the file. */


/* Mask for determining file access modes. */
#define O_ACCMODE   (O_RDONLY|O_WRONLY|O_RDWR)

#endif  /* INCLUDE_METALC_FCNTL_H_ */
