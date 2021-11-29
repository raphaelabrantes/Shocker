//1
// Created by godofall on 08/11/2021.
//
#include <EventManager.h>


namespace EventManager{

    EventManager::EventManager(Controller::ControllerInputReader &controllerInputReader):
        _controllerInputReader(controllerInputReader) {
    }

    [[noreturn]] void EventManager::start() {
        auto *event = new js_event;
        do{
            _controllerInputReader.getEvent(event);
            std::cout << static_cast<int>(event->type) << " " << static_cast<int>(event->number) << " " << static_cast<short>(event->value) << std::endl;
        }
        while(true);

    }
}
