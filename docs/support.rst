Supported Headers
=================


* **assert.h**:
* **ctype.h**: Complete support.
* **errno.h**: Complete support. Note that this is *not* thread-safe.
* **fenv.h**:
* **float.h**:  *Must be provided by the toolchain compiler.*
* **inttypes.h**:
* **iso646.h**: *Must provided by the toolchain compiler.*
* **limits.h**: *Must provided by the toolchain compiler.*
* **locale.h**: Partial; only the default C locale is supported. There's no such thing
  as a "local" locale; using ``setlocale()`` with ``""`` as the locale has no effect.
* **math.h**:
* **setjmp.h**:
* **signal.h**:
* **stdarg.h**: *Must provided by the toolchain compiler.*
* **stdbool.h**: Compatibility shim present for compilers that don't provide it.
* **stddef.h**: *Must provided by the toolchain compiler.*
* **stdint.h**: Minimal compatibility shim present for compilers that don't provide it.
* **stdio.h**:
* **stdlib.h**:
* **string.h**: Complete support.
* **tgmath.h**:
* **time.h**:
* **uchar.h**:
* **wchar.h**:
* **wctype.h**:

Supported Features
==================

* Pointer mangling: No
* Red zone: No
* Shadow stack: Optional. Define METALC_X86_USE_SHADOW_STACK=1 at compile time to enable it.
* Stack canaries: No

Additional Features
===================

These are additional features not part of the C standard library.


Requirements
============

Use of ``malloc()`` requires implementing the POSIX standard function ``brk()``
