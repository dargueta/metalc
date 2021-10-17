cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# TODO (dargueta): Maybe modify this to support NASM-compatible assemblers like YASM?
project(MetalC VERSION 0.1.0 LANGUAGES C ASM_NASM)

# Compile as C90 with no extensions enabled. This must be 100% cross-platform.
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)


if(CMAKE_C_COMPILER_ID STREQUAL "MinGW")  # TODO: MinGW may lie and say it's GCC
    set(METALC_COMPILER_MINGW 1)
    set(METALC_ABI_MICROSOFT 1)
    set(METALC_ABI_GNU 0)
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|LLVM")
    set(METALC_COMPILER_GCC 1)
    set(METALC_ABI_GNU 1)
    set(METALC_ABI_MICROSOFT 0)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    message(
        FATAL_ERROR "Microsoft Visual Studio is explicitly not supported, as cross-compilation is a nightmare. Please use MinGW or Cygwin."
    )
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_C_COMPILER_ID}")
endif()

# Enable all warnings, make warnings errors. This applies to *all* targets.
add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

include("settings.cmake")

enable_testing()
include("CTest")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_BINARY_DIR}/lib")
