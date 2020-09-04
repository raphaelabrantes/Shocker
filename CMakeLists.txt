cmake_minimum_required(VERSION 3.10)
# set the project name
project(DualShocker C CXX)
# add the executable
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
add_executable(DualSocker main.cpp controller.cpp controller.h events.cpp events.h)