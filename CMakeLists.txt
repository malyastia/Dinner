cmake_minimum_required(VERSION 3.4)

project(dining_philosophers)

set(CMAKE_CXX_STANDARD 17)

add_executable(dining_philosophers src/dinner.cpp)

target_link_libraries(dining_philosophers dining_philosophers_exec)

add_subdirectory(src)
