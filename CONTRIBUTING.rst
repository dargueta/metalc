Contributing
============

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD",
"SHOULD NOT", "RECOMMENDED",  "MAY", and "OPTIONAL" in this document are to be
interpreted as described in `RFC 2119`_.

Marking C Library Functions
---------------------------

All implemented C standard library functions MUST be specially marked in the
headers where they're declared and in the files where they're implemented.

In the header where the file is declared, after the function is declared you MUST
add a call to the ``cstdlib_export`` or ``cstdlib_export_with_attr`` macro with
the name of the function, like so:

.. code-block:: c

    /* string.h */
    size_t strcspn(const char *str1, const char *str2);
    char *strerror(int errnum);

    cstdlib_export_with_attr(strcspn, nonnull);
    cstdlib_export(strerror);

Side note: ``cstdlib_export_with_attr`` accepts multiple arguments, so you're
not limited to a single attribute.

In the file where the function is implemented, *after* the code implementing the
function, you MUST add a call to the ``cstdlib_implement`` macro:

.. code-block:: c

    /* string.c */

    size_t strcspn(const char *str1, const char *str2) {
        /* ... */
    }
    cstdlib_implement(strcspn);

Failure to do so will result in the function either being invisible to the linker,
being overridden by the host OS's C standard library when testing, and other
unpredictable behavior.

.. _RFC 2119: https://tools.ietf.org/html/rfc2119
