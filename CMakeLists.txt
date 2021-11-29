cmake_minimum_required(VERSION 3.10)
# set the project name
project(DualShocker C CXX)
# add the executable
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
include_directories(src/include)
add_executable(NewShocker src/main.cpp src/ControllerInputReader.cpp src/EventManager.cpp)
target_compile_options(NewShocker PRIVATE -Wall -Wextra -Wpedantic -Werror)
add_executable(DualSocker main.cpp controller.cpp controller.h events.cpp events.h parser.cpp parser.h vinput.cpp vinput.h)