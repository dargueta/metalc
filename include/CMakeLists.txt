include("CheckIncludeFile")

check_include_file("float.h" METALC_HAVE_FLOAT_H)
check_include_file("limits.h" METALC_HAVE_LIMITS_H)
check_include_file("stdarg.h" METALC_HAVE_STDARG_H)
check_include_file("stdbool.h" METALC_HAVE_STDBOOL_H)
check_include_file("stddef.h" METALC_HAVE_STDDEF_H)
check_include_file("stdint.h" METALC_HAVE_STDINT_H)


# ============================= SYSTEM PROFILING ============================= #
# Generate a header file to tell MetalC about the system we're compiling for.

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/metalc.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/metalc/metalc.h"
    ESCAPE_QUOTES
    @ONLY
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/x86/metalc.asm.in"
    "${CMAKE_CURRENT_BINARY_DIR}/metalc/x86/metalc.inc"
    @ONLY
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/x86/setjmp.inc"
    "${CMAKE_CURRENT_BINARY_DIR}/metalc/x86/setjmp.inc"
    @ONLY
)


set(HEADER_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/assert.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/atomic.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/crtinit.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/ctype.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/errno.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/fcntl.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/float.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/iso646.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/kernel_hooks.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/limits.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/locale.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/math.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/posix.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/setjmp.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/signal.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/stdarg.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/stdbool.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/stddef.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/stdint.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/stdio.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/stdlib.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/string.h"
)

set(BITS_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/bits/stddef.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/metalc/bits/stdio.h"
)

list(
    TRANSFORM
    HEADER_FILES
    REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
    OUTPUT_VARIABLE HEADER_OUTPUT_FILES
)

list(
    TRANSFORM
    BITS_FILES
    REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
    OUTPUT_VARIABLE BITS_OUTPUT_FILES
)


add_custom_target(
    metalc_headers ALL
    "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/metalc" "${CMAKE_CURRENT_BINARY_DIR}/metalc/bits" "${CMAKE_CURRENT_BINARY_DIR}/metalc/x86"
    COMMAND "${CMAKE_COMMAND}" -E copy ${HEADER_FILES} "${CMAKE_CURRENT_BINARY_DIR}/metalc"
    COMMAND "${CMAKE_COMMAND}" -E copy ${BITS_FILES} "${CMAKE_CURRENT_BINARY_DIR}/metalc/bits"
    COMMENT "Generating target header files"
    DEPENDS ${HEADER_FILES} ${BITS_FILES}
    BYPRODUCTS ${HEADER_OUTPUT_FILES} ${BITS_OUTPUT_FILES}
    COMMAND_EXPAND_LISTS
    VERBATIM
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")
