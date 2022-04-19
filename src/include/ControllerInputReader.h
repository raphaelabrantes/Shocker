//
// Created by godofall on 06/11/2021.
//

#pragma once
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
        explicit ControllerInputReader(std::string& filename);
        ~ControllerInputReader();
        void getEvent(js_event *event) const;
    private:
        int file;

    };
}