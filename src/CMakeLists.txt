cmake_minimum_required(VERSION 3.4)

project(prog)

set(CMAKE_CXX_STANDARD 17)

add_executable(prog dinner.cpp)

target_link_libraries(prog PUBLIC pthread)
