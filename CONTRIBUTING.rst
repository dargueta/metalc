Contributing
============

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD",
"SHOULD NOT", "RECOMMENDED",  "MAY", and "OPTIONAL" in this document are to be
interpreted as described in `RFC 2119`_.

Prefixes
--------

The problem with testing an implementation of the standard C library is it exports
functions and global variables with the same name as the host system's standard
C library. Thus we can't compare functionality directly without annoying amounts
of black magic, animal sacrifice, and messing with the linker.

To get around this, MetalC uses certain prefixes on its exported items. These
are left on when testing:

.. code-block:: c

    assert(__mcapi_strlen("foo") == strlen("foo"));

When compiling the final library, a simple script will remove the prefix(es) so
the library will contain the expected ``strlen`` instead of ``__mcapi_strlen``,
``errno`` instead of ``__mcapi_errno``, and so on.

There are a few kinds of prefixes, which MUST be applied to the applicable functions,
structs, variables, macros, etc. in their implementations, header files, and *all*
usages. Failure to do so can result in MetalC accidentally calling the host OS's
standard C library, and the final compiled library will be missing functions.

+--------------+-----------------------------------------------------------------+
| Prefix       | Description                                                     |
+==============+=================================================================+
| ``__mcapi_`` | REQUIRED for things we want to expose to users as part of the   |
|              | *public* C API. This includes all functions and variables in the|
|              | ANSI C99 library, in addition to nonstandard things we implement|
|              | like ``itoa()``.                                                |
+--------------+-----------------------------------------------------------------+
| ``__mcint_`` | REQUIRED for things we want to expose to users but aren't meant |
|              | to be used directly. For example, the ``assert()`` macro aliases|
|              | ``__mcint_assert`` when ``NDEBUG`` is not defined.              |
|              | ``__mcint_assert`` needs to be accessible to programs using this|
|              | library, but it's not supposed to be used directly.             |
+--------------+-----------------------------------------------------------------+

.. _RFC 2119: https://tools.ietf.org/html/rfc2119
