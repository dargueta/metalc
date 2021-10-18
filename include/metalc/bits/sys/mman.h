/**
 * @file mman.h
 */

#ifndef INCLUDE_METALC_BITS_SYS_MMAN_H_
#define INCLUDE_METALC_BITS_SYS_MMAN_H_

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
#endif  /* METALC_DISABLE_STDLIB_DEFS */

#endif  /* INCLUDE_METALC_BITS_SYS_MMAN_H_ */
