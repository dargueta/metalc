/**
 * Function pointers and character set definitions for multi-byte character support.
 * @file common.h
 */

#ifndef INCLUDE_METALC_CHARSETS_COMMON_H_
#define INCLUDE_METALC_CHARSETS_COMMON_H_

#include "../stddef.h"
#include "../wchar.h"


typedef int (*fptr_mblen)(const char *str, size_t n);
typedef int (*fptr_wctomb)(char *str, __mcapi_wchar_t wchar);
typedef int (*fptr_mbtowc)(__mcapi_wchar_t *pwc, const char *str, size_t n);


struct __mcint_charset_info {
    /** The normalized name of the character set. */
    const char * const name;

    /** A pointer to the function implementing @ref mblen for this character set. */
    const fptr_mblen f_mblen;

    /** A pointer to the function implementing @ref mbtowc for this character set. */
    const fptr_mbtowc f_mbtowc;

    /** A pointer to the function implementing @ref wctomb for this character set. */
    const fptr_wctomb f_wctomb;
};

#endif  /* INCLUDE_METALC_CHARSETS_COMMON_H_ */
