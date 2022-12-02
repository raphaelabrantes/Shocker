// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <iostream>
#include <JsonMapper.h>
#include <ControllerInputReader.h>
#include <EventManager.h>
int main(int argc, char *argv[]) {
    std::string joystickDeviceFile("/dev/input/js0");
    const std::string configPath = getenv("HOME") +
                                   std::string("/.config/shocker/");
    std::string profileFile(configPath + "profiles/default.json");
    if (argc < 1) {
        profileFile.assign(argv[1]);
    }
    uinput_setup uinputSetup {};
    auto keybinding = JsonMapper::createMapping(profileFile, configPath);
    start_env(keybinding, uinputSetup);
    Controller::ControllerInputReader controllerInputReader(joystickDeviceFile);
    EventConverter eventConverter(std::move(keybinding));
    EventManager::EventManager eventManager(controllerInputReader,
                                            eventConverter);
    eventManager.start();
}
