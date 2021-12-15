//1
// Created by godofall on 08/11/2021.
//
#include <EventManager.h>
#include <fstream>
#include <linux/uinput.h>
#include <Action.h>


namespace EventManager {

    EventManager::EventManager(Controller::ControllerInputReader &controllerInputReader,
                               std::unordered_map<std::string, Actions::Action *> &keyMap) :
            _controllerInputReader(controllerInputReader), _keyMap(keyMap) {
        _fd = start_env(_keyMap, uinputSetup);

    }

    [[noreturn]] void EventManager::start() {
        auto *event = new js_event;
        do {
            _controllerInputReader.getEvent(event);
            std::cout << static_cast<int>(event->type) << " " << static_cast<int>(event->number) << " "
                      << static_cast<int16_t>(event->value) << std::endl;

        } while (true);

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