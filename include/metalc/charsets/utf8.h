#ifndef INCLUDE_METALC_CHARSETS_UTF8_H_
#define INCLUDE_METALC_CHARSETS_UTF8_H_

#include <metalc/stddef.h>
#include <metalc/wchar.h>


/**
 * Implementation of @ref mblen for UTF-8.
 */
METALC_API_INTERNAL int __mcint_utf8_mblen(const char *str, size_t n);


/**
 * Implementation of @ref mbtowc for UTF-8.
 */
METALC_API_INTERNAL int __mcint_utf8_mbtowc(__mcapi_wchar_t *pwc, const char *str, size_t n);


/**
 * Implementation of @ref wctomb for UTF-8.
 */
METALC_API_INTERNAL int __mcint_utf8_wctomb(char *str, __mcapi_wchar_t wchar);



#endif  /* INCLUDE_METALC_CHARSETS_UTF8_H_ */
