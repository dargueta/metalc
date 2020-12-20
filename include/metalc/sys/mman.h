/**
 * @file mman.h
 */

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


#define __mcapi_MAP_PRIVATE     1   /**< Changes are private. */
#define __mcapi_MAP_SHARED      2   /**< Share changes. */


/**
 * The mapping isn't backed by a file.
 *
 * The memory is initialized to zeros.
 */
#define __mcapi_MAP_ANONYMOUS   4


/** Compatibility alias for @ref MAP_ANONYMOUS */
#define __mcapi_MAP_ANON        __mcapi_MAP_ANONYMOUS


/**
 * Don't interpret addr as a hint: place the mapping at exactly that address.
 */
#define __mcapi_MAP_FIXED   8

#endif  /* INCLUDE_METALC_SYS_MMAN_H_ */
