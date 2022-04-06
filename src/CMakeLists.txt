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
        include/Shocker.h)

set_target_properties(Shocker
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/Action.h;include/ControllerInputReader.h;include/EventConverter.h;include/EventManager.h;include/JsonMapper.h;include/Shocker.h"
        )
target_include_directories(Shocker PUBLIC include)
install(TARGETS Shocker
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )


install(FILES include/nlohmann/json.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nlohmann/
        )