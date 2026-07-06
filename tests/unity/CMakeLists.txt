add_library(unity STATIC unity.c)

target_include_directories(unity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
