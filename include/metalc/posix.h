#ifndef INCLUDE_METALC_POSIX_H_
#define INCLUDE_METALC_POSIX_H_

#include <metalc/metalc.h>
#include <metalc/stddef.h>


METALC_API_INTERNAL int __mclib_brk(void *new_brk);
METALC_API_INTERNAL void *__mclib_sbrk(intptr_t diff);

#endif  /* INCLUDE_METALC_POSIX_H_ */
