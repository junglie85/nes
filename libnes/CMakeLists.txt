add_library(libnes cpu.c)
target_compile_options(libnes PRIVATE -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
