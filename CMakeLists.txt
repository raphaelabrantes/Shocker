cmake_minimum_required(VERSION 3.10)
# set the project name
project(DualShocker C CXX)
# add the executable
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")
add_subdirectory(src)
add_executable(NewShocker
        main.cpp
        )
target_link_libraries(NewShocker $<TARGET_OBJECTS:Shocker>)
target_compile_options(NewShocker PRIVATE -Wall -Wextra -Wpedantic -Werror)