ABI Compatibility
=================

Calling Conventions
-------------------

The Microsoft and System V/GNU calling conventions are supported, with some
limitations:

64-bit code
~~~~~~~~~~~

Code compiled for 64-bit processors uses the calling convention mandated by the
compiler. Routines implemented in assembly language adhere to this.

32-bit code
~~~~~~~~~~~

Functions written in assembly language use the `fastcall`_ calling convention
unless ``-fno-fastcall-internals`` was passed to the configuration script, in
which case the functions use the compiler's default calling convention.

.. _fastcall: https://en.wikipedia.org/wiki/X86_calling_conventions#Microsoft_fastcall
