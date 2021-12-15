//
// Created by godofall on 06/11/2021.
//
#include <iostream>
#include <ControllerInputReader.h>
#include <EventManager.h>
#include <JsonMapper.h>

int main(int argc, char *argv[]) {
    std::string joystickDeviceFile("/dev/input/js0");
    std::string profileFile("profiles/text.json");
    if(argc < 1){
        profileFile.assign(argv[1]);
    }

    auto keybinding = JsonMapper::createMapping(profileFile);
    Controller::ControllerInputReader controllerInputReader(joystickDeviceFile);
    EventManager::EventManager eventManager(controllerInputReader, keybinding);
    //eventManager.start();
}