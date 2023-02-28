cmake_minimum_required(VERSION 3.10)
# set the project name
project(Shocker LANGUAGES C CXX VERSION 1.0.0 DESCRIPTION "Lib do Shocker" )



# add the executable
add_library(Shocker
        Action.cpp
        ControllerInputReader.cpp
        EventConverter.cpp
        EventManager.cpp
        JsonMapper.cpp
        Controller.cpp)
target_include_directories(Shocker PUBLIC include)