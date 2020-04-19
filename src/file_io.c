/* Implements fopen, fread, fwrite, etc. */

#include <metalc/crtinit.h>
#include <metalc/errno.h>
#include <metalc/fcntl.h>
#include <metalc/kernel_hooks.h>
#include <metalc/stdio.h>
#include <metalc/stdlib.h>
#include <metalc/string.h>


extern MetalCRuntimeInfo *__mclib_runtime_info;

struct __mcint_FILE {
    intptr_t descriptor;
    int eof;
    int last_error;
    int io_flags;
};


static struct __mcint_FILE _internal_stdin;
static struct __mcint_FILE _internal_stdout;
static struct __mcint_FILE _internal_stderr;

__mcapi_FILE * const __mcapi_stdin = &_internal_stdin;
__mcapi_FILE * const __mcapi_stdout = &_internal_stdout;
__mcapi_FILE * const __mcapi_stderr = &_internal_stderr;


METALC_API_INTERNAL int fileio_init(void) {
    memset(&_internal_stdin, 0, sizeof(_internal_stdin));
    memset(&_internal_stdout, 0, sizeof(_internal_stdout));
    memset(&_internal_stderr, 0, sizeof(_internal_stderr));

    _internal_stdin.descriptor = __mclib_runtime_info->stdin_handle;
    _internal_stdin.io_flags = O_RDONLY;

    _internal_stdout.descriptor = __mclib_runtime_info->stdout_handle;
    _internal_stdout.io_flags = O_WRONLY;

    _internal_stderr.descriptor = __mclib_runtime_info->stderr_handle;
    _internal_stderr.io_flags = O_WRONLY;
    return 0;
}


METALC_API_INTERNAL int fileio_teardown(void) {
    fclose(__mcapi_stdin);
    fclose(__mcapi_stdout);
    fclose(__mcapi_stderr);
    return 0;
}


int __mcint_mode_string_to_flags(const char *mode) {
    int can_read, can_write, append, binary, truncate, create, excl, i, result;

    can_read = can_write = append = binary = truncate = create = excl = 0;

    /* First character must be 'r', 'w', or 'a'. */
    switch (mode[0]) {
        case 'r':
            can_read = 1;
            break;
        case 'w':
            can_write = 1;
            truncate = 1;
            create = 1;
            break;
        case 'a':
            can_write = 1;
            create = 1;
            append = 1;
            break;
        default:
            __mcapi_errno = __mcapi_EINVAL;
            return -1;
    }

    /* We can now have any of '+', 'b', and 'x' in any order, or none of these
     * at all. Iterate through the rest of the mode string and find what we can,
     * puking if there's anything we don't recognize. */
    for (i = 1; mode[i] != '\0'; ++i) {
        switch (mode[i]) {
            case '+':
                can_read = can_write = 1;
                break;
            case 'b':
                binary = 1;
                break;
            case 'x':
                /* `x` is only valid with `w` */
                if (mode[0] != 'w') {
                    __mcapi_errno = __mcapi_EINVAL;
                    return -1;
                }
                excl = 1;
                break;
            default:
                __mcapi_errno = __mcapi_EINVAL;
                return -1;
        }
    }

    if (can_read && !can_write)
        result = O_RDONLY;
    else if (can_write && !can_read)
        result = O_WRONLY;
    else
        result = O_RDWR;

    if (append)
        result |= O_APPEND;
    if (create)
        result |= O_CREAT;
    if (truncate)
        result |= O_TRUNC;
    if (excl)
        result |= O_EXCL;
    if (binary)
        result |= O_BINARY;

    return result;
}


void clearerr(__mcapi_FILE *stream) {
    stream->last_error = 0;
    stream->eof = 0;
}


void fclose(__mcapi_FILE *stream) {
    krnlhook_fsync(stream->descriptor, __mclib_runtime_info->udata);
    krnlhook_close(stream->descriptor, __mclib_runtime_info->udata);
    free(stream);
}


int feof(__mcapi_FILE *stream) {
    return stream->eof;
}


int ferror(__mcapi_FILE *stream) {
    return stream->last_error;
}


__mcapi_FILE *fopen(const char *path, const char *mode) {
    __mcapi_FILE *stream;
    int io_flags;

    /* Convert the OS-agnostic mode string to POSIX bit flags, which will be
     * easier for the kernel to deal with. */
    io_flags = __mcint_mode_string_to_flags(mode);
    if (io_flags == -1) {
        __mcapi_errno = __mcapi_EINVAL;
        return NULL;
    }

    stream = malloc(sizeof(*stream));
    if (stream == NULL)
        return NULL;

    /* Open the file, always using mode 0644 if we're creating a new file. */
    stream->descriptor = krnlhook_open(
        path, io_flags, 0644, __mclib_runtime_info->udata
    );
    if (stream->descriptor == -1) {
        free(stream);
        return NULL;
    }

    stream->eof = 0;
    stream->last_error = 0;
    stream->io_flags = io_flags;
    return stream;
}


size_t fwrite(const void *ptr, size_t size, size_t count, __mcapi_FILE *stream) {
    /* Complain if we're trying to write to a read-only stream. */
    if ((stream->io_flags & O_ACCMODE) == O_RDONLY) {
        __mcapi_errno = __mcapi_EPERM;
        return ~0;
    }

    /* Seek to the end of the stream if we opened the file in append mode. */
    if (stream->io_flags & O_APPEND)
        fseek(stream, 0, __mcapi_SEEK_END);

    return krnlhook_write(
        stream->descriptor, ptr, size * count, __mclib_runtime_info->udata
    );
}


size_t fread(void *ptr, size_t size, size_t count, __mcapi_FILE *stream) {
    /* Complain if we're trying to read from a write-only stream. */
    if ((stream->io_flags & O_ACCMODE) == O_WRONLY) {
        __mcapi_errno = __mcapi_EPERM;
        return ~0;
    }

    return krnlhook_read(
        stream->descriptor, ptr, size * count, __mclib_runtime_info->udata
    );
}


__mcapi_fpos_t fseek(__mcapi_FILE *stream, long offset, int whence) {
    return krnlhook_seek(
        stream->descriptor, offset, whence, __mclib_runtime_info->udata
    );
}


cstdlib_implement(clearerr);
cstdlib_implement(fclose);
cstdlib_implement(feof);
cstdlib_implement(ferror);
cstdlib_implement(fopen);
cstdlib_implement(fwrite);
cstdlib_implement(fread);
cstdlib_implement(fseek);
