add_subdirectory(unity)

add_executable(test_color_converter test_color_convert.c)

target_link_libraries(test_color_converter PRIVATE color_converter unity)

add_test(NAME color_converter_test COMMAND test_color_converter)
