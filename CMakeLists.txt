cmake_minimum_required(VERSION 3.4)

project(dining_philosophers)
add_executable(dining_philosophers dinner.cpp )

set(CMAKE_CXX_STANDARD 17)

# add_subdirectory(
target_include_directories(${PROJECT_NAME} PUBLIC philosopher waiter)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)