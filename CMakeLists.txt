cmake_minimum_required(VERSION 3.16)

project(color_converter LANGUAGES C)

add_library(color_converter INTERFACE)

target_include_directories(color_converter INTERFACE include)
