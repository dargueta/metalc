Build System Configurations
===========================

This directory contains build system configurations for all supported toolchains. The directory
structure is as follows:

::

    toolchain-suite
    |
    +--. target-platform
       |
       +--. ABI
          |
          +-- compiler.in
          +-- linker.in
          +-- assembler.in

Each ``.in`` file you see is a template that will be compiled into a Makefile that will be included
by the main Makefile. It defines all the required settings for each build configuration (debug,
test, and production).
