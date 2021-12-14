//
// Created by godofall on 12/12/2021.
//
#include <Action.h>

#include <utility>
#include <unistd.h>


namespace Actions {
    Action::Action(std::string command) : _command(std::move(command)) {}


    Button::Button(int key, int fd) : Action(""), _fd(fd), _key(key) {}

    void Button::activate() {
        _inputEvent.type = EV_KEY;
        _inputEvent.code = _key;
        _inputEvent.value = 1;
        emit();
        sync();
    }

    void Button::deactivate() {
        _inputEvent.type = EV_KEY;
        _inputEvent.code = _key;
        _inputEvent.value = 0;
        emit();
        sync();
    }

    void Button::emit() {
        write(_fd, &_inputEvent, sizeof(_inputEvent));
    }

    void Button::sync() {
        _inputEvent.type = EV_SYN;
        _inputEvent.code = SYN_REPORT;
        _inputEvent.value = 0;
        emit();
    }


}