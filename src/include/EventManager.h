//
// Created by godofall on 07/11/2021.
//

#ifndef DUALSHOCKER_EVENTMANAGER_H
#define DUALSHOCKER_EVENTMANAGER_H

#include <functional>
#include <ControllerInputReader.h>
#include <nlohmann/json.hpp>
#include <linux/uinput.h>

extern "C" {
int start_env(nlohmann::json &js, uinput_setup &setup);
}

namespace EventManager {
    class EventManager {
    public:
        EventManager(Controller::ControllerInputReader &controllerInputReader);

        [[noreturn]] void start();

    private:
        Controller::ControllerInputReader _controllerInputReader;
        nlohmann::json keys;
        int pd;
        uinput_setup uinputSetup;
    };
}

#endif //DUALSHOCKER_EVENTMANAGER_H
