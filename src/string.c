#include "metalc/errno.h"
#include "metalc/metalc.h"
#include "metalc/stdio.h"
#include "metalc/stdlib.h"
#include "metalc/string.h"
#include "metalc/locale.h"


/* These are copied and pasted from the Linux headers on Ubuntu 19.10. */
static const char *ERROR_STRINGS[mclib__MAX_ERRNO] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Cannot access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error",
};


void *memchr(const void *ptr, int value, size_t num) {
    const unsigned char *p;

    for (p = ptr; num != 0; --num, ++p) {
        if (*p == (unsigned char)value)
            return (void *)p;
    }
    return NULL;
}
cstdlib_implement(memchr);


int memcmp(const void *ptr1, const void *ptr2, size_t num) {
    const signed char *left, *right;
    int diff;

    diff = 0;
    left = ptr1;
    right = ptr2;

    for (; (num > 0) && (diff == 0); ++left, ++right, --num)
        diff = *left - *right;

    return diff;
}
cstdlib_implement(memcmp);


void *memcpy(void *destination, const void *source, size_t num) {
    char *p_dest;
    const char *p_src;

    p_dest = destination;
    p_src = source;

    for (; num > 0; --num)
        *p_dest++ = *p_src++;

    return destination;
}
cstdlib_implement(memcpy);


void *memmove(void *destination, const void *source, size_t num) {
    char *p_dest;
    const char *p_src;

    if ((destination == source) || (num == 0))
        return destination;
    else if (destination < source) {
        /* Moving source backwards. We can copy from the beginning of the source
         * onwards. */
        p_dest = destination;
        p_src = source;

        for (; num > 0; --num)
            *p_dest++ = *p_src++;
    }
    else {
        /* Moving source forwards. To avoid stomping on the end of the source
         * we need to copy from the end of the source back to the beginning. */
        p_dest = (char *)destination + num - 1;
        p_src = (char *)source + num - 1;

        for (; num > 0; --num)
            *p_dest-- = *p_src--;
    }

    return destination;
}
cstdlib_implement(memmove);


void *memset(void *ptr, int value, size_t num) {
    unsigned char *p_dest;

    for (p_dest = (unsigned char *)ptr; num > 0; --num)
        *p_dest++ = (unsigned char)value;

    return ptr;
}
cstdlib_implement(memset);


char *strcat(char *destination, const char *source) {
    return strcpy(strchr(destination, 0), source);
}
cstdlib_implement(strcat);


char *strchr(const char *str, int character) {
    do {
        if (*str == (char)character)
            return (char *)str;
    } while (*str++ != '\0');

    return NULL;
}
cstdlib_implement(strchr);


int strcmp(const char *str1, const char *str2) {
    int diff = 0;

    for (; (*str1 != '\0') && (*str2 != '\0'); ++str1, ++str2) {
        diff = *str1 - *str2;
        if (diff != 0)
            return diff;
    }

    return *(signed char *)str1 - *(signed char *)str2;
}
cstdlib_implement(strcmp);


int strcoll(const char *str1, const char *str2) {
    return mcinternal_ptr_current_coll->f_strcoll(str1, str2);
}
cstdlib_implement(strcoll);


char *strcpy(char *destination, const char *source) {
    char *p_dest = destination;

    do {
        *p_dest++ = *source;
    } while (*source++ != '\0');

    return destination;
}
cstdlib_implement(strcpy);


size_t strcspn(const char *str1, const char *str2) {
    size_t span;

    /**
     * @todo There must be a better way of implementing this than O(n^2).
     */
    for (span = 0; *str1 != '\0'; ++str1, ++span) {
        if (strchr(str2, (int)*str1))
            return span;
    }
    return span;
}
cstdlib_implement(strcspn);


char *strerror(int errnum) {
    static char buffer[128];

    if ((errnum >= 0) && (errnum < mclib__MAX_ERRNO))
        return strcpy(buffer, ERROR_STRINGS[errnum]);

    sprintf(buffer, "Unknown error %d", errnum);
    return buffer;
}
cstdlib_implement(strerror);


size_t strlen(const char *str) {
    size_t length = 0;

    while (str[length] != '\0')
        ++length;
    return length;
}
cstdlib_implement(strlen);


char *strncat(char *destination, const char *source, size_t num) {
    char *p_dest;

    /* Return early if `num` is 0 to avoid a potentially expensive call to
     * strlen(). */
    if (num == 0)
        return destination;

    p_dest = destination + strlen(destination);

    for (; (num > 0) && (*source != '\0'); --num)
        *p_dest++ = *source++;

    *p_dest = '\0';
    return destination;
}
cstdlib_implement(strncat);


int strncmp(const char *str1, const char *str2, size_t num) {
    int diff = 0;

    while ((num > 0) && (*str1 != '\0') && (*str2 != '\0')) {
        diff = *str1 - *str2;
        if (diff != 0)
            return diff;

        --num;
        ++str1;
        ++str2;
    }

    /* When we get out here either 1) num is 0 and all characters matched so far,
     * or 2) num > 0, and we hit the end of one or both strings. In case 1 we
     * want to return 0, otherwise compare the last characters. */

    if (num == 0)
        return 0;
    return (int)(*str1 - *str2);
}
cstdlib_implement(strncmp);


char *strncpy(char *destination, const char *source, size_t num) {
    char *p_dest = destination;

    for (; (num > 0) && (*source != '\0'); --num)
        *p_dest++ = *source++;

    for (; num > 0; --num)
        *p_dest++ = '\0';

    return destination;
}
cstdlib_implement(strncpy);


char *strpbrk(const char *str1, const char *str2) {
    size_t span = strcspn(str1, str2);

    if (str1[span] == '\0')
        return NULL;
    return (char *)str1 + span;
}
cstdlib_implement(strpbrk);


char *strrchr(const char *str, int character) {
    const char *p_end;

    for (p_end = str + strlen(str); p_end != str; --p_end) {
        if (*p_end == (char)character)
            return (char *)p_end;
    }
    return NULL;
}
cstdlib_implement(strrchr);


size_t strspn(const char *str1, const char *str2) {
    size_t span = 0;

    for (; *str1 != '\0'; ++str1, ++span) {
        if (strchr(str2, *str1) == NULL)
            break;
    }
    return span;
}
cstdlib_implement(strspn);


char *strstr(const char *str, const char *substr) {
    size_t substr_length = strlen(substr);

    for (; *str != '\0'; ++str) {
        if (strncmp(str, substr, substr_length) == 0)
            return (char *)str;
    }
    return NULL;
}
cstdlib_implement(strstr);


char *strtok(char *str, const char *delimiters) {
    size_t token_length;
    static char *start = NULL;

    if (str != NULL)
        start = str;

    if (start == NULL)
        /* Edge case: `str` is null and so is `start`. Treat this as an empty
         * string with no tokens. */
        return NULL;

    if (*start == '\0')
        return NULL;

    /* Search for the first character in `start` that *isn't* a delimiter. If we
     * hit EOS, bail and return NULL forevermore. */
    for (; *start != '\0'; ++start) {
        if (strchr(delimiters, *start) == NULL)
            break;
    }

    /* Hit the end of the string so there are no more tokens. Bail. */
    if (*start == '\0')
        return NULL;

    /* else: Found the beginning of the next token. Now search for the next
     * delimiter. */
    token_length = strcspn(start, delimiters);

    /* Found the first delimiter or hit EOS. Stomp over it with a null. */
    start[token_length] = '\0';
    return start;
}
cstdlib_implement(strtok);


size_t strxfrm(char *destination, const char *source, size_t num) {
    return mcinternal_ptr_current_coll->f_strxfrm(destination, source, num);
}
cstdlib_implement(strxfrm);


size_t strcpy_and_update_buffer(const char *source, void **buffer) {
    size_t buffer_size = strlen(source);

    strcpy(*(char **)buffer, source);
    *(char **)buffer += buffer_size;
    return buffer_size;
}


size_t strncpy_and_update_buffer(const char *source, void **buffer, size_t n) {
    size_t source_size, buffer_size;

    source_size = strlen(source);
    buffer_size = (source_size < n) ? source_size : n;

    strncpy(*(char **)buffer, source, n);
    *(char **)buffer += buffer_size;
    return buffer_size;
}
