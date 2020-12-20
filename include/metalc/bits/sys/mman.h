/**
 * @file mman.h
 */

#ifndef INCLUDE_METALC_BITS_SYS_MMAN_H_
#define INCLUDE_METALC_BITS_SYS_MMAN_H_

#ifndef METALC_DISABLE_STDLIB_DEFS
    #define PROT_NONE       __mcapi_PROT_NONE
    #define PROT_READ       __mcapi_PROT_READ
    #define PROT_WRITE      __mcapi_PROT_WRITE
    #define PROT_EXEC       __mcapi_PROT_EXEC
    #define MAP_FAILED      __mcapi_MAP_FAILED
    #define MAP_PRIVATE     __mcapi_MAP_PRIVATE
    #define MAP_SHARED      __mcapi_MAP_SHARED
    #define MAP_ANONYMOUS   __mcapi_MAP_ANONYMOUS
    #define MAP_FIXED       __mcapi_MAP_FIXED
#endif  /* METALC_DISABLE_STDLIB_DEFS */

#endif  /* INCLUDE_METALC_BITS_SYS_MMAN_H_ */
