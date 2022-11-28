// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <EventManager.h>
#include <linux/uinput.h>
#include <Action.h>
#include <Exception.h>
#include <fcntl.h>
#include <csignal>


namespace EventManager {

    EventManager::EventManager(
            Controller::ControllerInputReader &controllerInputReader,
            EventConverter &eventConverter,
            std::unordered_map<std::string,
                    Actions::Action *> &keyMap) :
            _eventConverter(eventConverter),
            _controllerInputReader(&controllerInputReader),
            _keyMap(keyMap) {
        _fd = start_env(_keyMap, uinputSetup);
    }

    void EventManager::start() {
        running = true;
        auto *event = new js_event;
        do {
            _controllerInputReader->getEvent(event);
#ifdef DEGUB
            std::cout << "TYPE: " <<
            static_cast<int>(event->type) <<
            " KEY: " <<
            static_cast<int>(event->number)<<
            " VALUE: "
            << event->value << std::endl;
#endif
            if (event->type == JS_EVENT_AXIS) {
                dealWithTriggers(event);
            } else {
                dealWithButtons(event);
            }
        } while (running);
    }

    void EventManager::dealWithButtons(js_event *event) const {
        auto action = _eventConverter.convert(event);
        if (event->value) {
            action->activate(event->value);
        } else {
            action->deactivate();
        }
    }

    void EventManager::dealWithTriggers(js_event *event) const {
        if (!(event->number == 2 || event->number == 5)) {
            if (event->value == 0) {
                event->value = -1;
                auto action1 = _eventConverter.convert(event);
                event->value = 4;
                auto action2 = _eventConverter.convert(event);
                action1->deactivate();
                action2->deactivate();
            } else {
                dealWithButtons(event);
            }
        }
    }

    EventManager::~EventManager() {
        ioctl(_fd, UI_DEV_DESTROY);
        close(_fd);
    }
}  // namespace EventManager

int start_env(const std::unordered_map<std::string, Actions::Action *> &map,
              uinput_setup &uinputSetup) {
    int fd = open("/dev/uinput",
                  O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        std::cout << "It was not possible to"
                     " create the keyboard and mouse device" << std::endl;
        throw UnableToCreateVirtualDevice();
    }
    ioctl(fd, UI_SET_EVBIT, EV_REL);
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
    for (auto &it : map) {
        it.second->initiate(fd);
    }
    memset(&uinputSetup, 0, sizeof(uinputSetup));
    uinputSetup.id.bustype = BUS_USB;
    uinputSetup.id.vendor = 0x1234;
    uinputSetup.id.product = 0x5678;
    strcpy(uinputSetup.name, "Shocker Keyboard and Mouse");
    ioctl(fd, UI_DEV_SETUP, &uinputSetup);
    ioctl(fd, UI_DEV_CREATE);
    return fd;
}
