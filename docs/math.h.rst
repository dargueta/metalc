Support for math.h
==================

**Note:**

Functions taking a ``long double`` as an argument, such as ``sinl``, ``cosl``,
etc. are implemented, but only present in the library *if* the compiler supports
``long double`` type. There's no way around this.

Implemented
-----------

* ``sin``
* ``sinf``
* ``sinl``
* ``cos``
* ``cosf``
* ``cosl``
* ``tan``
* ``tanf``
* ``tanl``

Not Yet Implemented
-------------------

* ``acos``
* ``acosf``
* ``acosl``
* ``asin``
* ``asinf``
* ``asinl``

Will Not Be Implemented
-----------------------
