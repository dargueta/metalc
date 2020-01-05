Metal Standard C Library
========================

This is an implementation of the C standard library designed for use by:

* Programs that run with no underlying operating system, or
* UEFI applications.

This library requires your C compiler to provide a few headers of its own, namely:

* float.h
* limits.h
* stdarg.h
* stddef.h
* stdint.h (a partial shim is provided that'll work for some systems without it)

GCC's freestanding mode provides all of these headers; MinGW probably does as
well.

Caveat
------

I *really* don't want to pay USD 201.10 for a copy of the C standard from the
ISO's website. Therefore, the bulk of this library is built on me going through
the standard library reference on `cplusplus.com <https://cplusplus.com>`_,
implementing functions one by one, and testing them against the GCC implementation.

While I will do my absolute best to keep this as close as possible to expected
behavior, I cannot guarantee this is 100% accurate.

Compilation Modes
-----------------

This library can be compiled in one of several modes, depending on the needs of
the program linking to it.

* **Bare:** No OS support. A number of features are missing, but this is still
  useful for writing an OS kernel.
* **Partial:** Features missing in "bare" mode are present, but the host program
  (e.g. a kernel) must implement some hooks.
* **UEFI:** Uses the UEFI API to provide I/O, memory allocation, etc. Useful for
  writing OS bootloaders.

Build Requirements
------------------

To build this library you'll need:

* CMake 3.8 or higher
* A compiler supporting ANSI C99 or later, such as GCC or MinGW. Visual Studio
  cannot cross-compile and so is not supported.
* (UEFI mode only) A UEFI library implementation, such as `GNU_EFI`_ or `TianoCore`_.

License
-------

I'm releasing this under the terms of the New BSD License. See LICENSE.txt for
the full legal text.

.. _GNU_EFI: https://sourceforge.net/projects/gnu-efi/
.. _TianoCore: https://www.tianocore.org/
