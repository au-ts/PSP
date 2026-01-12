# This is a list of modules that is included as a fixed/base set
# when this PSP is selected.  They must exist under fsw/modules.

# NOTE: This set is REQUIRED for all versions of the platform.
# If a module only works on some versions of the platform, add
# if to psp_conditional_modules.cmake instead

# timebase_lionsos
# iodriver
# ram_direct
eeprom_notimpl
port_notimpl
timebase_posix_clock
