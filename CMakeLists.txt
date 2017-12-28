cmake_minimum_required(VERSION 3.7)
project(CppPrimer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(CppEssential ${SOURCE_FILES})

add_executable(ch3_vector ch3/vector.cpp)
add_executable(ch3_string ch3/string.cpp)
add_executable(ch3_container ch3/container.cpp)
add_executable(ch3_base_type ch3/base_type.cpp)
add_executable(ch3_array ch3/array.cpp)

add_executable(ch4_operator ch4/operator.cpp)

add_executable(ch6_function ch6/function.cpp)

add_executable(ch7_sales_data ch7/Sales_data.cpp ch7/Sales_data.h ch7/main.cpp ch7/Screen.h ch7/Account.cpp ch7/Account.h)

add_executable(ch8_stream ch8/stream.cpp)

add_executable(ch9_sequential_container ch9/sequential_container.cpp ch9/vector&string.cpp)

add_executable(ch10_generic_algprithm ch10/generic_algo.cpp)