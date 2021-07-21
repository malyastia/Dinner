cmake_minimum_required(VERSION 3.4)

add_library(dining_philosophers_exec SHARED dinner.cpp eventLog.hpp fork.hpp philosopher.hpp)

target_link_libraries(dining_philosophers_exec PUBLIC pthread)