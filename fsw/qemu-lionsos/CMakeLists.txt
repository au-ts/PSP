######################################################################
#
# CMAKE build recipe for qemu-lionsos PSP component
#
######################################################################

# This contains the fully platform-specific code to
# run CFE on this target.

# Build the qemu-lionsos implementation as a library
add_library(psp-${CFE_PSP_TARGETNAME}-impl OBJECT
    src/cfe_psp_exception.c
    src/cfe_psp_memory.c
    src/cfe_psp_ssr.c
    src/cfe_psp_start.c
    src/cfe_psp_support.c
    src/cfe_psp_watchdog.c
)

target_compile_options(psp-${CFE_PSP_TARGETNAME}-impl PRIVATE
    -std=gnu99
    -Wno-pedantic
    -Wno-unused-function
)

target_compile_definitions(psp-${CFE_SYSTEM_PSPNAME}-impl PRIVATE
    $<TARGET_PROPERTY:psp_module_api,INTERFACE_COMPILE_DEFINITIONS>
)

target_include_directories(psp-${CFE_PSP_TARGETNAME}-impl PRIVATE
    inc
    $<TARGET_PROPERTY:psp_module_api,INTERFACE_INCLUDE_DIRECTORIES>
)
