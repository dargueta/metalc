/**
 * @file mman.h
 */

#ifndef INCLUDE_METALC_SYS_MMAN_H_
#define INCLUDE_METALC_SYS_MMAN_H_

/** Pages cannot be accessed at all. */
#define PROT_NONE   0

/** Pages may be read from. */
#define PROT_READ   1

/** Pages may be written to. */
#define PROT_WRITE  2

/** Pages may be executed. */
#define PROT_EXEC   4

/**
 * The value returned by memory-mapping functions to indicate an error occurred.
 */
#define MAP_FAILED  ((void *)-1)


#define MAP_PRIVATE     1   /**< Changes are private. */
#define MAP_SHARED      2   /**< Share changes. */


/**
 * The mapping isn't backed by a file.
 *
 * The memory is initialized to zeros.
 */
#define MAP_ANONYMOUS   4


/** Compatibility alias for @ref MAP_ANONYMOUS */
#define MAP_ANON        MAP_ANONYMOUS


/**
 * Don't interpret addr as a hint: place the mapping at exactly that address.
 */
#define MAP_FIXED   8

#endif  /* INCLUDE_METALC_SYS_MMAN_H_ */
