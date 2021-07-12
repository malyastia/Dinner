cmake_minimum_required(VERSION 3.4)

project(prog)

set(CMAKE_CXX_STANDARD 17)

 add_executable(prog dinner.cpp)


find_package(Threads REQUIRED)
target_link_libraries(prog PRIVATE Threads::Threads)
