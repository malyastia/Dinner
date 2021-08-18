cmake_minimum_required(VERSION 3.4)

project(dining_philosophers)
add_executable(dining_philosophers dinner.cpp )

target_compile_features (${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PRIVATE philosopher_and_fork waiter lib)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)