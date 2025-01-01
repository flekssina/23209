cmake_minimum_required(VERSION 3.26)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab4 main.cpp)
configure_file(${CMAKE_SOURCE_DIR}/test.csv ${CMAKE_BINARY_DIR}/test.csv COPYONLY)

