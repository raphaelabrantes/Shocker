// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <Action.h>
#include <unistd.h>
#include <utility>
#include <iostream>


namespace Actions {
    Action::Action(std::string command) : _command(std::move(command)) {}

    std::string Action::getCommand() const {
        return _command;
    }


    Button::Button(int key) : Action(""), _key(key) {}

    void Button::activate(int16_t) {
        if (!_isPressed) {
            _inputEvent.type = EV_KEY;
            _inputEvent.code = _key;
            _inputEvent.value = 1;
            emit();
            sync();
            _isPressed = true;
        }
    }

    void Button::deactivate() {
        if (_isPressed) {
            _inputEvent.type = EV_KEY;
            _inputEvent.code = _key;
            _inputEvent.value = 0;
            emit();
            sync();
            _isPressed = false;
        }
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

    int Button::getKey() const {
        return _key;
    }

    void Button::initiate(int fd) {
        _fd = fd;
        ioctl(_fd, UI_SET_KEYBIT, _key);
    }

    Command::Command(std::string &command) : Action(
            std::move(command)),
            _done(true) {}

    void Command::activate(int16_t) {
        if (_done) {
            delete _thread;
            _thread = new std::thread(&Command::start, this);
            _thread->detach();
        }
    }

    void Command::deactivate() {
    }

    void Command::start() {
        _done = false;
        system(_command.c_str());
        _done = true;
    }

    Command::~Command() {
        delete _thread;
    }

    Macro::Macro(std::vector<Actions::Action *> actionVector) :
            _actionVector(std::move(actionVector)), Action("") {
    }

    void Macro::activate(int16_t) {
        for (auto it : _actionVector) {
            it->activate(1);
            it->deactivate();
        }
    }

    std::vector<Actions::Action *> Macro::getActions() const {
        return _actionVector;
    }


    void Macro::initiate(int fd) {
        for (auto action : _actionVector) {
            action->initiate(fd);
        }
    }

    Mouse::Mouse(int key, int sensibility, bool isPositive) :
            Button(key),
            _sensibility(sensibility),
            _isPositive(isPositive) {
    }

    void Mouse::activate(int16_t value) {
        _value = value;
        if (!_isPressed) {
            _isPressed = true;
            delete _mouseThread;
            _mouseThread = new std::thread(&Mouse::start, this);
            _mouseThread->detach();
        }
    }

    void Mouse::deactivate() {
        _isPressed = false;
    }

    void Mouse::start() {
        while (_isPressed) {
            _inputEvent.type = EV_REL;
            _inputEvent.code = getKey();
            __s32 x = _sensibility * abs(_value) / 32767;
            _inputEvent.value = _isPositive ? x : -x;
            emit();
            sync();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }

    void Mouse::initiate(int fd) {
        _fd = fd;
        ioctl(_fd, UI_SET_RELBIT, getKey());
    }


}  // namespace Actions
