//
// Created by godofall on 07/11/2021.
//

#ifndef DUALSHOCKER_EVENTMANAGER_H
#define DUALSHOCKER_EVENTMANAGER_H
#include <functional>
#include <ControllerInputReader.h>
namespace EventManager {
    class EventManager {
    public:
        EventManager(Controller::ControllerInputReader &controllerInputReader);
        [[noreturn]] void start();
    private:
        Controller::ControllerInputReader _controllerInputReader;
    };
}

#endif //DUALSHOCKER_EVENTMANAGER_H
