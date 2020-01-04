ABI Compatibility
=================


Calling Conventions
-------------------

Microsoft, System V/GNU, and Watcom calling conventions are supported, with
some limitations:

64-bit code
~~~~~~~~~~~

Code compiled for 64-bit processors uses the calling convention mandated by the
compiler. Routines implemented in assembly language adhere to this.

32-bit code
~~~~~~~~~~~

Functions written in assembly language use the `__fastcall`_ calling convention
on MinGW, Visual Studio, and GCC-compatible compilers. For the sake of simplicity
if you're using a Watcom compiler, the standard C calling convention is used.

.. ___fastcall:
