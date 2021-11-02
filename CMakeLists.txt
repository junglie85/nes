cmake_minimum_required(VERSION 3.20)
project(nes
    VERSION 0.1
    DESCRIPTION "NES Emulator"
    LANGUAGES C)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_EXTENSIONS OFF)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Disable the million other CTest targets that get created.
    # https://stackoverflow.com/questions/56089330/cmake-creates-lots-of-targets-i-didnt-specify
    set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
    include(CTest)
endif ()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(app)
add_subdirectory(libnes)

if (BUILD_TESTING OR NES_BUILD_TESTING)
    add_subdirectory(test)
endif ()
