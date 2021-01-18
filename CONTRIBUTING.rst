Contributing
============

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD",
"SHOULD NOT", "RECOMMENDED",  "MAY", and "OPTIONAL" in this document are to be
interpreted as described in `RFC 2119`_.

Marking C Library Functions
---------------------------

All implemented C standard library functions MUST be specially marked in the
headers where they're declared.

In the header where the file is declared, after the function is declared you MUST
use the ``METALC_API_EXPORT`` or ``METALC_API_EXPORT_WITH_ATTR`` macro before
the name of the function, like so:

.. code-block:: c

    /* string.h */
    METALC_API_EXPORT_WITH_ATTR(nonnull) size_t strcspn(const char *str1, const char *str2);
    METALC_API_EXPORT char *strerror(int errnum);

Side note: ``METALC_API_EXPORT_WITH_ATTR`` accepts multiple arguments, so you're
not limited to a single attribute.

.. _RFC 2119: https://tools.ietf.org/html/rfc2119
