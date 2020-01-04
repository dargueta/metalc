# Set to 1 to compile the C library for use by a kernel. Leave it at 0 to compile
# for client programs.
set(METALC_COMPILE_FOR_KERNEL ${COMPILE_FOR_KERNEL})

# Enable EFI. Requires cross-compiling with an EFI toolchain.
set(METALC_COMPILE_OPTION_USE_EFI ${USE_EFI})

# 32- and 64-bit x86 targets only: Enable use of the shadow stack.
set(METALC_COMPILE_OPTION_X86_USE_SHADOW_STACK ${X86_USE_SHADOW_STACK})

# Do NOT use functions written in assembly language if they're available.
set(METALC_COMPILE_OPTION_DISABLE_ASM_IMPLEMENTATIONS 0)

# (x86-32 only) Should internal functions use the `fastcall` calling convention?
set(METALC_INTERNALS_USE_FASTCALL 1)


set(METALC_TARGET_ARCHITECTURE_ID ${ARCHITECTURE_ID})
set(METALC_TARGET_ARCHITECTURE_BITS ${ARCHITECTURE_BITS})
set(TARGET_PROCESSOR "${TARGET_PROCESSOR}")

add_definitions(${C_DEFINES})


if (METALC_COMPILE_OPTION_USE_EFI EQUAL 1)
    set(METALC_COMPILE_OPTION_ENABLE_ALL_IO 1)
else()
    set(METALC_COMPILE_OPTION_ENABLE_ALL_IO ${ENABLE_ALL_IO})
endif()


# TODO (dargueta): Make these independent options if possible (and if it makes sense).
set(METALC_COMPILE_OPTION_ENABLE_DISK_IO ${ENABLE_ALL_IO})
set(METALC_COMPILE_OPTION_ENABLE_TERM_IO ${ENABLE_ALL_IO})
set(METALC_COMPILE_OPTION_ENABLE_FILE_IO ${ENABLE_ALL_IO})
