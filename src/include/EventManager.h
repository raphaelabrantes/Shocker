//
// Created by godofall on 07/11/2021.
//

#ifndef DUALSHOCKER_EVENTMANAGER_H
#define DUALSHOCKER_EVENTMANAGER_H

#include <functional>
#include <ControllerInputReader.h>
#include <nlohmann/json.hpp>
#include <linux/uinput.h>
#include <Action.h>

extern "C" {
int start_env(const std::unordered_map<std::string, Actions::Action*>& map, uinput_setup &setup);
}

namespace EventManager {
    class EventManager {
    public:
        EventManager(Controller::ControllerInputReader &controllerInputReader,
                     std::unordered_map<std::string, Actions::Action *> &keyMap);

        ~EventManager();
        [[noreturn]] void start();

    private:
        Controller::ControllerInputReader _controllerInputReader;
        std::unordered_map<std::string, Actions::Action *> _keyMap;
        int _fd;
        uinput_setup uinputSetup = {};
    };
}

#endif //DUALSHOCKER_EVENTMANAGER_H