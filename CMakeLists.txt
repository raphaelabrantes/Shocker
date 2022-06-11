cmake_minimum_required(VERSION 3.10)
# set the project name
project(DualShocker C CXX)
# add the executable
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
set(CMAKE_CXX_CPPLINT "cpplint")
find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_subdirectory(src)
add_executable(NewShocker
        main.cpp
        )
add_executable(ShockerGUI mainGUI.cpp)

target_link_libraries(NewShocker Shocker)
target_link_libraries(ShockerGUI Shocker Qt5::Widgets)


target_compile_options(NewShocker  PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_options(ShockerGUI PRIVATE -Wall -Wextra -Wpedantic -Werror)
install(DIRECTORY key_codes profiles DESTINATION $ENV{HOME}/.config/shocker)
install(FILES icon/Shocker.desktop DESTINATION $ENV{HOME}/.local/share/applications)
install(FILES icon/shocker_icon.png DESTINATION /usr/share/icons)
install(TARGETS NewShocker ShockerGUI RUNTIME)
