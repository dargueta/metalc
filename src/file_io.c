/* Implements fopen, fread, fwrite, etc. */

#include "metalc/crtinit.h"
#include "metalc/errno.h"
#include "metalc/fcntl.h"
#include "metalc/kernel_hooks.h"
#include "metalc/stdio.h"
#include "metalc/stdlib.h"
#include "metalc/string.h"

extern MetalCRuntimeInfo *mcinternal_runtime_info;

struct mcinternal_FILE
{
    int descriptor;
    int eof;
    int last_error;
    int io_flags;
};

static struct mcinternal_FILE mcinternal_stdin;
static struct mcinternal_FILE mcinternal_stdout;
static struct mcinternal_FILE mcinternal_stderr;

mclib_FILE *const mclib_stdin = &mcinternal_stdin;
mclib_FILE *const mclib_stdout = &mcinternal_stdout;
mclib_FILE *const mclib_stderr = &mcinternal_stderr;

METALC_ATTR__NO_EXPORT
int fileio_init(void)
{
    memset(&mcinternal_stdin, 0, sizeof(mcinternal_stdin));
    memset(&mcinternal_stdout, 0, sizeof(mcinternal_stdout));
    memset(&mcinternal_stderr, 0, sizeof(mcinternal_stderr));

    mcinternal_stdin.descriptor = mcinternal_runtime_info->stdin_handle;
    mcinternal_stdin.io_flags = O_RDONLY;

    mcinternal_stdout.descriptor = mcinternal_runtime_info->stdout_handle;
    mcinternal_stdout.io_flags = O_WRONLY;

    mcinternal_stderr.descriptor = mcinternal_runtime_info->stderr_handle;
    mcinternal_stderr.io_flags = O_WRONLY;
    return 0;
}

METALC_ATTR__NO_EXPORT
int fileio_teardown(void)
{
    fclose(mclib_stdin);
    fclose(mclib_stdout);
    fclose(mclib_stderr);
    return 0;
}

int mcinternal_mode_string_to_flags(const char *mode)
{
    int can_read, can_write, append, binary, truncate, create, excl, i, result;

    can_read = can_write = append = binary = truncate = create = excl = 0;

    /* First character must be 'r', 'w', or 'a'. */
    switch (mode[0])
    {
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
        mclib_errno = mclib_EINVAL;
        return -1;
    }

    /* We can now have any of '+', 'b', and 'x' in any order, or none of these
     * at all. Iterate through the rest of the mode string and find what we can,
     * puking if there's anything we don't recognize. */
    for (i = 1; mode[i] != '\0'; ++i)
    {
        switch (mode[i])
        {
        case '+':
            can_read = can_write = 1;
            break;
        case 'b':
            binary = 1;
            break;
        case 'x':
            /* `x` is only valid with `w` */
            if (mode[0] != 'w')
            {
                mclib_errno = mclib_EINVAL;
                return -1;
            }
            excl = 1;
            break;
        default:
            mclib_errno = mclib_EINVAL;
            return -1;
        }
    }

    if (can_read && can_write)
        result = O_RDWR;
    else if (can_read)
        result = O_RDONLY;
    else
        result = O_WRONLY;

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

void clearerr(mclib_FILE *stream)
{
    stream->last_error = 0;
    stream->eof = 0;
}

void fclose(mclib_FILE *stream)
{
    krnlhook_fsync(stream->descriptor);
    krnlhook_close(stream->descriptor);

    /* Don't free the standard I/O streams, as they were never allocated with
     * malloc. */
    if ((stream != &mcinternal_stdin) && (stream != &mcinternal_stdout) &&
        (stream != &mcinternal_stderr))
        free(stream);
}

int feof(mclib_FILE *stream)
{
    return stream->eof;
}

int ferror(mclib_FILE *stream)
{
    return stream->last_error;
}

mclib_FILE *fopen(const char *path, const char *mode)
{
    mclib_FILE *stream;
    int io_flags;

    /* Convert the OS-agnostic mode string to POSIX bit flags, which will be
     * easier for the kernel to deal with. */
    io_flags = mcinternal_mode_string_to_flags(mode);
    if (io_flags == -1)
    {
        mclib_errno = mclib_EINVAL;
        return mclib_NULL;
    }

    stream = malloc(sizeof(*stream));
    if (stream == mclib_NULL)
        return mclib_NULL;

    /* Open the file, always using mode 0644 if we're creating a new file. */
    stream->descriptor = krnlhook_open(path, io_flags, 0644);
    if (stream->descriptor == -1)
    {
        /* Failed to open the file. */
        free(stream);
        return mclib_NULL;
    }

    stream->eof = 0;
    stream->last_error = 0;
    stream->io_flags = io_flags;
    return stream;
}

size_t fwrite(const void *ptr, size_t size, size_t count, mclib_FILE *stream)
{
    /* Complain if we're trying to write to a read-only stream. */
    if ((stream->io_flags & O_ACCMODE) == O_RDONLY)
    {
        mclib_errno = mclib_EPERM;
        return ~0;
    }

    /* Seek to the end of the stream if we opened the file in append mode. */
    if (stream->io_flags & O_APPEND)
        fseek(stream, 0, mclib_SEEK_END);

    return krnlhook_write(stream->descriptor, ptr, size * count);
}

size_t fread(void *ptr, size_t size, size_t count, mclib_FILE *stream)
{
    /* Complain if we're trying to read from a write-only stream. */
    if ((stream->io_flags & O_ACCMODE) == O_WRONLY)
    {
        mclib_errno = mclib_EPERM;
        return ~0;
    }

    return krnlhook_read(stream->descriptor, ptr, size * count);
}

mclib_fpos_t fseek(mclib_FILE *stream, long offset, int whence)
{
    return krnlhook_seek(stream->descriptor, offset, whence);
}

cstdlib_implement(clearerr);
cstdlib_implement(fclose);
cstdlib_implement(feof);
cstdlib_implement(ferror);
cstdlib_implement(fopen);
cstdlib_implement(fwrite);
cstdlib_implement(fread);
cstdlib_implement(fseek);
