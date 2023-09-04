project(11_table)

file(GLOB SRC_FILES *.cpp)
add_executable(test_11_table ${SRC_FILES})
target_link_libraries(test_11_table gtest_main gmock)

add_test(NAME test_11_table COMMAND test_11_table)
