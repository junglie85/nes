add_executable(test_cpu test_cpu.c ${CMAKE_SOURCE_DIR}/extern/unity/src/unity.c ${CMAKE_SOURCE_DIR}/libnes/cpu.c)
target_include_directories(test_cpu PUBLIC ${CMAKE_SOURCE_DIR}/extern/unity/src)
target_include_directories(test_cpu PUBLIC ${CMAKE_SOURCE_DIR})
add_test(TestCPU test_cpu)
