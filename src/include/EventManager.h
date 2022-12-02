// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once
#include <memory>
#include <linux/uinput.h>
#include <ControllerInputReader.h>
#include <nlohmann/json.hpp>
#include <Action.h>
#include <EventConverter.h>



int start_env(const std::unordered_map<std::string, std::shared_ptr<Actions::Action>>& map, uinput_setup &setup);
void stop_env(int fd);

namespace EventManager {
    class EventManager {
     public:
        EventManager(Controller::ControllerInputReader &controllerInputReader,
                     EventConverter &eventConverter);
        void start();

        void stop() { running = false; };

     private:
        EventConverter* _eventConverter;
        Controller::ControllerInputReader* _controllerInputReader;
        std::atomic_bool running = {};

        void dealWithTriggers(js_event *event) const;

        void dealWithButtons(js_event *event) const;
    };
} // namespace EventManager
