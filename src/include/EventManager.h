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


namespace EventManager {
    class EventManager {
     public:
        EventManager(Controller::ControllerInputReader &controllerInputReader,
                     EventConverter &eventConverter);
        void start();

        void stop() {
            m_running = false;
            m_eventConverter->stopAll();
        };

     private:
        EventConverter* m_eventConverter;
        Controller::ControllerInputReader* m_controllerInputReader;
        std::atomic_bool m_running = {};

        void dealWithTriggers(js_event *event) const;

        void dealWithButtons(js_event *event) const;
    };
} // namespace EventManager
