# The Microkit system description file expects self-contained
# program images so we must compile everything statically
set(CMAKE_EXE_EXPORTS_C_FLAG "-Wl,-static")
