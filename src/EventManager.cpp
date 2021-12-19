//1
// Created by godofall on 08/11/2021.
//
#include <EventManager.h>
#include <fstream>
#include <linux/uinput.h>
#include <Action.h>


namespace EventManager {

    EventManager::EventManager(Controller::ControllerInputReader &controllerInputReader,
                               EventConverter &eventConverter,
                               std::unordered_map<std::string, Actions::Action *> &keyMap) :
            _eventConverter(eventConverter), _controllerInputReader(controllerInputReader), _keyMap(keyMap) {
        _fd = start_env(_keyMap, uinputSetup);

    }

    [[noreturn]] void EventManager::start() {
        auto *event = new js_event;
        do {
            _controllerInputReader.getEvent(event);
            std::cout << "TYPE: " << static_cast<int>(event->type) << "KEY: " << static_cast<int>(event->number)
                      << " VALUE: " << event->value << std::endl;
            if (event->type == JS_EVENT_AXIS) {
                dealWithTriggers(event);
            } else {
                dealWithButtons(event);
            }

        } while (true);

    }

    void EventManager::dealWithButtons(js_event *event) const {
        auto action = _eventConverter.convert(event);
        if (event->value) {
            action->activate(1);
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
}

int start_env(const std::unordered_map<std::string, Actions::Action *> &map, uinput_setup &uinputSetup) {
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        std::cout << "It was not possible to create the device" << std::endl;
        exit(1);
    }
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    for (auto &it: map) {
        if (it.second->getCommand().empty()) {
            auto *button = dynamic_cast<Actions::Button *>(it.second);
            if (button) {
                button->setFd(fd);
                ioctl(fd, UI_SET_KEYBIT, button->getKey());
            } else {
                assert(false);
            }
        }
    }
    memset(&uinputSetup, 0, sizeof(uinputSetup));
    uinputSetup.id.bustype = BUS_USB;
    uinputSetup.id.vendor = 0x1234;
    uinputSetup.id.product = 0x5678;
    strcpy(uinputSetup.name, "Shocker Keyboard");
    ioctl(fd, UI_DEV_SETUP, &uinputSetup);
    ioctl(fd, UI_DEV_CREATE);
    return fd;

}