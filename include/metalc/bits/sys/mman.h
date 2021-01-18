/**
 * @file mman.h
 */

#ifndef INCLUDE_METALC_BITS_SYS_MMAN_H_
#define INCLUDE_METALC_BITS_SYS_MMAN_H_

#ifndef METALC_DISABLE_STDLIB_DEFS
    #define PROT_NONE       PROT_NONE
    #define PROT_READ       PROT_READ
    #define PROT_WRITE      PROT_WRITE
    #define PROT_EXEC       PROT_EXEC
    #define MAP_FAILED      MAP_FAILED
    #define MAP_PRIVATE     MAP_PRIVATE
    #define MAP_SHARED      MAP_SHARED
    #define MAP_ANONYMOUS   MAP_ANONYMOUS
    #define MAP_FIXED       MAP_FIXED
#endif  /* METALC_DISABLE_STDLIB_DEFS */

#endif  /* INCLUDE_METALC_BITS_SYS_MMAN_H_ */
