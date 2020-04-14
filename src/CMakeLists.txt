set(LIBRARY_C_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/assert.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/crtinit.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/ctype.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/errno.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/file_io.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/kernel_hooks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/locale.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/malloc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/math.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/posix.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/signal.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/stdio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/stdlib.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/string.c"
)

set(LIBRARY_X86_ASM_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_PROCESSOR}/atomic.asm"
    "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_PROCESSOR}/setjmp.asm"
)

set(TEST_SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/ctype.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/file_io.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/string.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/testing.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/testing.h"
)

include_directories("${CMAKE_BINARY_DIR}/include")

if (TARGET_PROCESSOR STREQUAL "x86_16" OR TARGET_PROCESSOR STREQUAL "x86_32" OR TARGET_PROCESSOR STREQUAL "x86_64")
    set(ASM_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_PROCESSOR}/atomic.asm"
        "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_PROCESSOR}/setjmp.asm"
    )
else()
    # Hopefully this'll work for the rest of the architectures we're going to
    # try to support
    set(ASM_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_PROCESSOR}/atomic.s"
        "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_PROCESSOR}/setjmp.s"
    )
endif()

add_library(metalc_asm STATIC ${ASM_SOURCES})

if (METALC_COMPILE_FOR_TESTING)
    add_compile_options(-O0 -g)
endif()


# MetalC, compiled as a dynamic library for linking with other programs. Given
# that the major selling point of this library is that you'll used on bare metal
# or UEFI, you'll only need this as your system's standard C library when loading
# other programs. Your kernel won't be using this.
add_library(metalc SHARED ${LIBRARY_C_SOURCES})
add_dependencies(metalc metalc_asm metalc_headers)
target_compile_options(metalc PRIVATE -ffreestanding -Wextra -pedantic -pedantic-errors)
target_compile_definitions(
    metalc PRIVATE
    -DMETALC_BUILDING_LIBC=1
    -DMETALC_BUILD_KIND_SHARED=1
    -DMETALC_COMPILE_FOR_TESTING=${METALC_COMPILE_FOR_TESTING}
)
target_link_libraries(metalc metalc_asm)


# MetalC, compiled as a static library. You'll probably want to use this with
# your kernel or bootloader, since you'd need to write a dynamic linker to be
# able to use the shared one.
add_library(metalcstatic STATIC ${LIBRARY_C_SOURCES})
add_dependencies(metalcstatic metalc_asm metalc_headers)
target_compile_options(metalcstatic PRIVATE -Wextra -ffreestanding -pedantic -pedantic-errors)
target_compile_definitions(
    metalcstatic PRIVATE
    -DMETALC_BUILDING_LIBC=1
    -DMETALC_BUILD_KIND_STATIC=1
    -DMETALC_COMPILE_FOR_TESTING=${METALC_COMPILE_FOR_TESTING}
)
target_link_libraries(metalcstatic metalc_asm)


# Unit testing
if (METALC_COMPILE_FOR_TESTING)
    add_executable(test_executable ${TEST_SOURCE_FILES})
    add_dependencies(test_executable metalc metalc_headers)
    target_link_libraries(test_executable metalc)

    # Disable linking the executable with the OS's C standard library and use our
    # implementation instead.
    target_compile_options(
        test_executable PRIVATE
        -Wextra
        -pedantic
        -pedantic-errors
        -Wno-declaration-after-statement    # TODO: This should not be necessary
        -Wno-unused-variable                # Triggered by some macros we use
    )
    target_compile_definitions(
        test_executable PRIVATE
        -DMETALC_COMPILE_FOR_TESTING=1
        -DMETALC_DISABLE_STDLIB_DEFS=1
    )
endif()
