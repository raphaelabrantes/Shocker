// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <linux/joystick.h>
#include <string>
#include <fstream>
namespace Controller {

    class ControllerInputReader {
    public:
        explicit ControllerInputReader(std::string &filename);

        ~ControllerInputReader();

        void getEvent(js_event *event);

    private:
        std::ifstream jsStream;

    };
}