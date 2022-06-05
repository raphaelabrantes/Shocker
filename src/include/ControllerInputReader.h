// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

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