cmake_minimum_required(VERSION 3.4)


#add_executable(dining_philosophers_exec src/dinner.cpp)

add_executable(dining_philosophers dinner.cpp eventLog.hpp fork.hpp philosopher.hpp waiter.hpp)

target_link_libraries(dining_philosophers PRIVATE pthread)