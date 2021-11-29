//
// Created by godofall on 06/11/2021.
//
#include <iostream>
#include <ControllerInputReader.h>
#include <EventManager.h>
int main(int argc, char *argv[]) {
    std::cout << argc << argv[0] << std::endl;
    std::string filename("/dev/input/js0");

    Controller::ControllerInputReader controllerInputReader(filename);
    EventManager::EventManager eventManager(controllerInputReader);
    eventManager.start();
}