add_executable(nes main.c)
target_compile_options(nes PRIVATE -Werror -Wall -Wextra -Wconversion -Wsign-conversion)
target_include_directories(nes PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(nes PUBLIC libnes)
