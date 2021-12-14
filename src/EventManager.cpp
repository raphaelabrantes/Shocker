//1
// Created by godofall on 08/11/2021.
//
#include <EventManager.h>
#include <fstream>
#include <linux/uinput.h>


namespace EventManager {

    EventManager::EventManager(Controller::ControllerInputReader &controllerInputReader) :
            _controllerInputReader(controllerInputReader) {

    }

    [[noreturn]] void EventManager::start() {
        auto *event = new js_event;
        do {
            _controllerInputReader.getEvent(event);
            std::cout << static_cast<int>(event->type) << " " << static_cast<int>(event->number) << " "
                      << static_cast<int16_t>(event->value) << std::endl;

        } while (true);

    }
}

int start_env(nlohmann::json &js, uinput_setup &setup) {
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        std::cout << "It was not possible to create the device" << std::endl;
        exit(1);
    }
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    for (auto it = js.begin(); it != js.end(); ++it) {
        ioctl(fd, UI_SET_KEYBIT, static_cast<int>(it.value()));
    }
    memset(&setup, 0, sizeof(setup));
    setup.id.bustype = BUS_USB;
    setup.id.vendor = 0x1234;
    setup.id.product = 0x5678;
    strcpy(setup.name, "Shocker Keyboard");
    ioctl(fd, UI_DEV_SETUP, &setup);
    ioctl(fd, UI_DEV_CREATE);
    return fd;
}