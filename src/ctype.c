#include <metalc/ctype.h>
#include <metalc/metalc.h>


int isalnum(int c) {
    return isalpha(c) || isdigit(c);
}


int isalpha(int c) {
    return islower(c) || isupper(c);
}


int isblank(int c) {
    return (c == 0x20) || (c == 0x09);
}


int iscntrl(int c) {
    return c < 0x20;
}


int isdigit(int c) {
    return (c >= 0x30) && (c <= 0x39);
}


int isgraph(int c) {
    return (c >= 0x21) && (c < 0x7f);
}


int islower(int c) {
    return (c >= 0x61) && (c <= 0x7a);
}


int isprint(int c) {
    return (c >= 0x20) && (c < 0x7f);
}


int ispunct(int c) {
    return ((c >= 0x21) && (c <= 0x2f))     \
           || ((c >= 0x3a) && (c <= 0x40))  \
           || ((c >= 0x5b) && (c <= 0x60))  \
           || ((c >= 0x7b) && (c <= 0x7e));
}


int isspace(int c) {
    return ((c >= 0x09) && (c <= 0x0d)) || (c == 0x20);
}


int isupper(int c) {
    return (c >= 0x41) && (c <= 0x5a);
}


int isxdigit(int c) {
    return isdigit(c) || ((c >= 0x41) && (c <= 0x46)) || ((c >= 0x61) && (c <= 0x66));
}


int tolower(int c) {
    return isupper(c) ? c + 32 : c;
}


int toupper(int c) {
    return islower(c) ? c - 32 : c;
}


cstdlib_implement(isalnum);
cstdlib_implement(isalpha);
cstdlib_implement(isblank);
cstdlib_implement(iscntrl);
cstdlib_implement(isdigit);
cstdlib_implement(isgraph);
cstdlib_implement(islower);
cstdlib_implement(isprint);
cstdlib_implement(ispunct);
cstdlib_implement(isspace);
cstdlib_implement(isupper);
cstdlib_implement(isxdigit);
cstdlib_implement(tolower);
cstdlib_implement(toupper);
