include("CheckIncludeFile")

check_include_file("float.h" METALC_HAVE_FLOAT_H)
check_include_file("limits.h" METALC_HAVE_LIMITS_H)
check_include_file("stdarg.h" METALC_HAVE_STDARG_H)
check_include_file("stdbool.h" METALC_HAVE_STDBOOL_H)
check_include_file("stddef.h" METALC_HAVE_STDDEF_H)
check_include_file("stdint.h" METALC_HAVE_STDINT_H)


set(INCLUDE_ROOT_DIR "${MetalC_SOURCE_DIR}/include/metalc")
set(TEMPLATES_DIR "${MetalC_SOURCE_DIR}/templates")


configure_file(
    "${TEMPLATES_DIR}/include/metalc/metalc.h"
    "${INCLUDE_ROOT_DIR}/metalc.h"
    @ONLY
)

configure_file(
    "${TEMPLATES_DIR}/include/metalc/x86/metalc.inc"
    "${INCLUDE_ROOT_DIR}/x86/metalc.inc"
    @ONLY
)


set(HEADER_FILES
    "${INCLUDE_ROOT_DIR}/assert.h"
    "${INCLUDE_ROOT_DIR}/atomic.h"
    "${INCLUDE_ROOT_DIR}/crtinit.h"
    "${INCLUDE_ROOT_DIR}/ctype.h"
    "${INCLUDE_ROOT_DIR}/errno.h"
    "${INCLUDE_ROOT_DIR}/fcntl.h"
    "${INCLUDE_ROOT_DIR}/float.h"
    "${INCLUDE_ROOT_DIR}/iso646.h"
    "${INCLUDE_ROOT_DIR}/kernel_hooks.h"
    "${INCLUDE_ROOT_DIR}/limits.h"
    "${INCLUDE_ROOT_DIR}/locale.h"
    "${INCLUDE_ROOT_DIR}/math.h"
    "${INCLUDE_ROOT_DIR}/metalc.h"
    "${INCLUDE_ROOT_DIR}/posix.h"
    "${INCLUDE_ROOT_DIR}/setjmp.h"
    "${INCLUDE_ROOT_DIR}/signal.h"
    "${INCLUDE_ROOT_DIR}/stdarg.h"
    "${INCLUDE_ROOT_DIR}/stdbool.h"
    "${INCLUDE_ROOT_DIR}/stddef.h"
    "${INCLUDE_ROOT_DIR}/stdint.h"
    "${INCLUDE_ROOT_DIR}/stdio.h"
    "${INCLUDE_ROOT_DIR}/stdlib.h"
    "${INCLUDE_ROOT_DIR}/string.h"
    "${INCLUDE_ROOT_DIR}/bits/errno.h"
    "${INCLUDE_ROOT_DIR}/bits/printf.h"
    "${INCLUDE_ROOT_DIR}/bits/signal.h"
    "${INCLUDE_ROOT_DIR}/bits/stddef.h"
    "${INCLUDE_ROOT_DIR}/bits/stdio.h"
    "${INCLUDE_ROOT_DIR}/bits/stdlib_longlong.h"
    "${INCLUDE_ROOT_DIR}/charsets/common.h"
    "${INCLUDE_ROOT_DIR}/charsets/utf8.h"
)


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
    "${CMAKE_CURRENT_SOURCE_DIR}/printf.c"
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


add_library(metalc_asm STATIC ${ASM_SOURCES} ${HEADER_FILES})
target_compile_definitions(
    metalc_asm PRIVATE
    -DMETALC_BUILDING_LIBC=1
    -DMETALC_COMPILE_FOR_TESTING=${METALC_COMPILE_FOR_TESTING}
)

if (METALC_COMPILE_FOR_TESTING)
    add_compile_options(-O0 -g)
endif()


# MetalC, compiled as a dynamic library for linking with other programs. Given
# that the major selling point of this library is that you'll used on bare metal
# or UEFI, you'll only need this as your system's standard C library when loading
# other programs. Your kernel won't be using this.
add_library(metalc SHARED ${LIBRARY_C_SOURCES} ${HEADER_FILES})
add_dependencies(metalc metalc_asm)
target_compile_options(metalc PRIVATE -ffreestanding -Wextra -Wpedantic)
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
add_library(metalcstatic STATIC ${LIBRARY_C_SOURCES} ${HEADER_FILES})
add_dependencies(metalcstatic metalc_asm)
target_compile_options(metalcstatic PRIVATE -ffreestanding -Wextra -Wpedantic)
target_compile_definitions(
    metalcstatic PRIVATE
    -DMETALC_BUILDING_LIBC=1
    -DMETALC_BUILD_KIND_STATIC=1
    -DMETALC_COMPILE_FOR_TESTING=${METALC_COMPILE_FOR_TESTING}
)
target_link_libraries(metalcstatic metalc_asm)

include_directories("${MetalC_SOURCE_DIR}/include")

# Unit testing
if (METALC_COMPILE_FOR_TESTING)
    add_executable(test_executable ${TEST_SOURCE_FILES} ${HEADER_FILES})
    add_dependencies(test_executable metalc)
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
