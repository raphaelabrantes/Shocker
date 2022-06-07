cmake_minimum_required(VERSION 3.10)
# set the project name
project(DualShocker C CXX)
# add the executable
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
set(CMAKE_CXX_CPPLINT "cpplint")
add_subdirectory(src)
add_executable(NewShocker
        main.cpp
        )
target_link_libraries(NewShocker Shocker)
target_compile_options(NewShocker PRIVATE -Wall -Wextra -Wpedantic -Werror)
install(DIRECTORY key_codes profiles DESTINATION $ENV{HOME}/.config/shocker/)
install(TARGETS NewShocker RUNTIME)