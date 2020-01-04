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


file(GLOB METALC_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/metalc/*.h")
file(COPY ${METALC_HEADER_FILES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/metalc")

include_directories("${CMAKE_CURRENT_BINARY_DIR}")
