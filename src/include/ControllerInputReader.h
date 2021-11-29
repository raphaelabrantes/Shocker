//
// Created by godofall on 06/11/2021.
//

#ifndef DUALSHOCKER_CONTROLLERINPUTREADER_H
#define DUALSHOCKER_CONTROLLERINPUTREADER_H
#include <linux/joystick.h>
#include <fcntl.h>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <string>
#include <mutex>

namespace Controller {

    class ControllerInputReader {
    public:
        ControllerInputReader(std::string& filename);
        ~ControllerInputReader();
        void getEvent(js_event *event);
    private:
        int file;

    };
}
#endif //DUALSHOCKER_CONTROLLERINPUTREADER_H
