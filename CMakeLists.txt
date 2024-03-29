cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

# TODO (dargueta): Maybe modify this to support NASM-compatible assemblers like YASM?
project(MetalC VERSION 0.1.0 LANGUAGES C ASM_NASM)

# Compile as C99 with no extensions enabled. This must be 100% cross-platform.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)


if(CMAKE_C_PLATFORM_ID MATCHES "MinGW")
    set(METALC_COMPILER_MINGW 1)
    set(METALC_ABI_MICROSOFT 1)
    set(METALC_ABI_GNU 0)
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(METALC_COMPILER_GCC 1)
    set(METALC_ABI_GNU 1)
    set(METALC_ABI_MICROSOFT 0)
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_C_COMPILER_ID}")
endif()

include("settings.cmake")

enable_testing()
include("CTest")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_BINARY_DIR}/lib")
