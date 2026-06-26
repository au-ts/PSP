# The Microkit system description file expects self-contained
# program images so we must compile everything statically
set(CMAKE_EXE_EXPORTS_C_FLAG "-Wl,-static")

set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
set(CMAKE_SHARED_MODULE_SUFFIX ".elf")
