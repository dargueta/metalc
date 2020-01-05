#include <metalc/ctype.h>


int __mcapi_isalnum(int c) {
    return __mcapi_isalpha(c) || __mcapi_isdigit(c);
}


int __mcapi_isalpha(int c) {
    return __mcapi_islower(c) || __mcapi_isupper(c);
}


int __mcapi_isblank(int c) {
    return (c == 0x20) || (c == 0x09);
}


int __mcapi_iscntrl(int c) {
    return c < 0x20;
}


int __mcapi_isdigit(int c) {
    return (c >= 0x30) && (c <= 0x39);
}


int __mcapi_isgraph(int c) {
    return (c >= 0x21) && (c < 0x7f);
}


int __mcapi_islower(int c) {
    return (c >= 0x61) && (c <= 0x7a);
}


int __mcapi_isprint(int c) {
    return (c >= 0x20) && (c < 0x7f);
}


int __mcapi_ispunct(int c) {
    return ((c >= 0x21) && (c <= 0x2f))     \
           || ((c >= 0x3a) && (c <= 0x40))  \
           || ((c >= 0x5b) && (c <= 0x60))  \
           || ((c >= 0x7b) && (c <= 0x7e));
}


int __mcapi_isspace(int c) {
    return ((c >= 0x09) && (c <= 0x0d)) || (c == 0x20);
}


int __mcapi_isupper(int c) {
    return (c >= 0x41) && (c <= 0x5a);
}


int __mcapi_isxdigit(int c) {
    return __mcapi_isdigit(c) || ((c >= 0x41) && (c <= 0x46)) || ((c >= 0x61) && (c <= 0x66));
}


int __mcapi_tolower(int c) {
    return __mcapi_isupper(c) ? c + 32 : c;
}


int __mcapi_toupper(int c) {
    return __mcapi_islower(c) ? c - 32 : c;
}
