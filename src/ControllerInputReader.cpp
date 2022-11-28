// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE jsStream or at
// https://opensource.org/licenses/MIT.
#include <Exception.h>
#include <ControllerInputReader.h>

namespace Controller {
    ControllerInputReader::ControllerInputReader(std::string &jsStreamname) {
        jsStream.open(jsStreamname, std::fstream::in | std::fstream::binary);
        if (!jsStream.is_open()) {
            std::cout <<
                      "Unable to open joystick jsStream " <<
                      jsStreamname <<
                      std::endl <<
                      "Check if controller is connected." << std::endl;
            throw DeviceNotFound(jsStreamname);
        }
    }

    ControllerInputReader::~ControllerInputReader() {
        jsStream.close();
    }

    void ControllerInputReader::getEvent(js_event *event)  {
        ssize_t bytes;
        while (jsStream.read((char *) event, sizeof(js_event))) {
            if (event->type < JS_EVENT_INIT) {
                return;
            }
        }
        std::cout << "Controller Error (disconnected): " <<
                  static_cast<int>(bytes) << std::endl;
        throw DeviceDisconnected();
    }
}  // namespace Controller
