cmake_minimum_required(VERSION 3.16)

project(color_converter LANGUAGES C)

add_library(color_converter INTERFACE)

target_include_directories(color_converter INTERFACE
    include
)

option(COLOR_CONVERTER_BUILD_TESTS "Build tests" OFF)

if(COLOR_CONVERTER_BUILD_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()
