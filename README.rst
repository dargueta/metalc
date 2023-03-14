Bare Metal/UEFI Standard C Library
==================================

This is an implementation of the C standard library designed for use by:

* Programs that run with absolutely no underlying system (not even EFI),
* UEFI-aware OS kernels, or
* UEFI applications.

This library requires your C compiler to provide a few headers of its own, namely:

* float.h
* limits.h
* stdarg.h
* stddef.h
* stdint.h (a partial shim is provided that'll work for some systems without it)

GCC and compatible compilers' freestanding mode provides all of these headers.
Some versions of Visual Studio don't have stdint.h when building for the C99
standard, even though that header is part of the standard.

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

* **Bare:** Assumes no underlying system support. Many features such as I/O
  require hooks to be implemented by the code using the library.
* **UEFI Application:** Uses the UEFI boot services to provide I/O, memory
  allocation, etc. Useful for writing OS bootloaders and UEFI applications, but
  not OS kernels.
* **UEFI Kernel:** Uses the UEFI runtime API. Useful for OS kernels that rely on
  UEFI for certain hardware access.

Building
--------

Requirements
~~~~~~~~~~~~

To build this library you'll need:

* Python 3.3 or higher. (Python 2 may work but I make no guarantees and you
  really should reconsider the life choices that led you to still use it.)
* CMake 3.13 or higher
* A compiler supporting ANSI C99 or later, such as GCC, MinGW, OpenWatcom, etc.
  Visual Studio may or may not work.
* (UEFI modes only) If you're not building with an LLVM-based compiler like Clang,
  you'll also need a UEFI cross-compiler, such as `GNU_EFI`_ or `TianoCore`_.

Steps
~~~~~

1. Run ``configure`` with whatever options you need.
2. ``cmake -S . -B build``
3. ``make -C build``

If everything compiled correctly, the following files will be generated:

* ``include/metalc/``: The header files you'll need when using the library
* ``build/lib``:

  * ``libmetalc.so`` (extension could be .dll or .dylib depending on your OS):
    the shared library for dynamic linking.
  * ``libmetalcstatic.a`` (extension could also be ".lib" depending on your OS):
    the object file library for static linking.

You can ignore the other files.

License
-------

I'm releasing this under the terms of the New BSD License. See LICENSE.txt for
the full legal text.

.. _GNU_EFI: https://sourceforge.net/projects/gnu-efi/
.. _TianoCore: https://www.tianocore.org/
