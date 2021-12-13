//
// Created by godofall on 12/12/2021.
//
#include <Action.h>

#include <utility>
#include <unistd.h>


namespace Actions {
    Action::Action(std::string command) : _command(std::move(command)) {}


    Button::Button(const std::string &key, int fd) : Action(key), _fd(fd), _key(std::atoi(key.c_str())) {}

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