#ifndef INCLUDE_METALC_SYS_MMAN_H_
#define INCLUDE_METALC_SYS_MMAN_H_

/** Pages cannot be accessed at all. */
#define __mcapi_PROT_NONE   0

/** Pages may be read from. */
#define __mcapi_PROT_READ   1

/** Pages may be written to. */
#define __mcapi_PROT_WRITE  2

/** Pages may be executed. */
#define __mcapi_PROT_EXEC   4

/**
 * The value returned by memory-mapping functions to indicate an error occurred.
 */
#define __mcapi_MAP_FAILED  ((void *)-1)

#endif  /* INCLUDE_METALC_SYS_MMAN_H_ */
