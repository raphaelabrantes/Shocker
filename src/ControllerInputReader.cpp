// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <Exception.h>
#include <ControllerInputReader.h>

namespace Controller {
    ControllerInputReader::ControllerInputReader(std::string &filename) {
        file = open(filename.c_str(), O_RDONLY);
        if (file < 0) {
            std::cout <<
                      "Unable to open joystick file " <<
                      filename <<
                      std::endl <<
                      "Check if controller is connected." << std::endl;
            throw DeviceNotFound(filename);
        }
    }

    ControllerInputReader::~ControllerInputReader() {
        close(file);
    }

    void ControllerInputReader::getEvent(js_event *event) const {
        ssize_t bytes;
        while ((bytes = read(file, event, sizeof(*event))) > 0) {
            if (event->type < JS_EVENT_INIT) {
                return;
            }
        }
        std::cout << "Controller Error (disconnected): " <<
                  static_cast<int>(bytes) << std::endl;
        throw DeviceDisconnected();
    }
}  // namespace Controller
