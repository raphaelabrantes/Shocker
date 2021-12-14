cmake_minimum_required(VERSION 3.10)
# set the project name
project(DualShocker C CXX)
# add the executable
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
include_directories(src/include)
include_directories(libs)
add_executable(NewShocker
        src/main.cpp
        src/ControllerInputReader.cpp
        src/EventManager.cpp
        src/Action.cpp
        src/JsonMapper.cpp
        )
target_compile_options(NewShocker PRIVATE -Wall -Wextra -Wpedantic -Werror)