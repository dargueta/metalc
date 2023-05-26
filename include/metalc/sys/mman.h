/**
 * @file mman.h
 */

#ifndef INCLUDE_METALC_SYS_MMAN_H_
#define INCLUDE_METALC_SYS_MMAN_H_

#include "../stdint.h"

/** Pages cannot be accessed at all. */
#define mclib_PROT_NONE   0

/** Pages may be read from. */
#define mclib_PROT_READ   1

/** Pages may be written to. */
#define mclib_PROT_WRITE  2

/** Pages may be executed. */
#define mclib_PROT_EXEC   4

/**
 * The value returned by memory-mapping functions to indicate an error occurred.
 */
#define mclib_MAP_FAILED  ((void *)(~((uintptr_t)0)))

#define mclib_MAP_PRIVATE     1   /**< Changes are private. */
#define mclib_MAP_SHARED      2   /**< Share changes. */


/**
 * The mapping isn't backed by a file.
 *
 * The memory is initialized to zeros.
 */
#define mclib_MAP_ANONYMOUS   4


/** Compatibility alias for @ref MAP_ANONYMOUS */
#define mclib_MAP_ANON        mclib_MAP_ANONYMOUS


/**
 * Don't interpret addr as a hint: place the mapping at exactly that address.
 */
#define mclib_MAP_FIXED   8

/** Allow `mremap` to move the mapped memory if it can't extend the block. */
#define mclib_MREMAP_MAYMOVE    1

/** Move the memory mapping to a new location, and unmap the old location. */
#define mclib_MREMAP_FIXED      3

/** Remap a mapping to a new address but don't unmap the old block. */
#define mclib_MREMAP_DONTUNMAP  5

#ifndef METALC_DISABLE_STDLIB_DEFS
    #define PROT_NONE       mclib_PROT_NONE
    #define PROT_READ       mclib_PROT_READ
    #define PROT_WRITE      mclib_PROT_WRITE
    #define PROT_EXEC       mclib_PROT_EXEC
    #define MAP_FAILED      mclib_MAP_FAILED
    #define MAP_PRIVATE     mclib_MAP_PRIVATE
    #define MAP_SHARED      mclib_MAP_SHARED
    #define MAP_ANONYMOUS   mclib_MAP_ANONYMOUS
    #define MAP_FIXED       mclib_MAP_FIXED
    #define MREMAP_MAYMOVE      mclib_MREMAP_MAYMOVE
    #define MREMAP_FIXED        mclib_MREMAP_FIXED
    #define MREMAP_DONTUNMAP    mclib_MREMAP_DONTUNMAP
#endif  /* METALC_DISABLE_STDLIB_DEFS */

#endif  /* INCLUDE_METALC_SYS_MMAN_H_ */
