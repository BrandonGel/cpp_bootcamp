cmake_minimum_required(VERSION 3.10.0)
project(cpp_bootcamp VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(cpp_bootcamp main.cpp)

set_property(TARGET cpp_bootcamp PROPERTY CXX_STANDARD 23)