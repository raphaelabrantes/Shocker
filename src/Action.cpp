//
// Created by godofall on 12/12/2021.
//
#include <Action.h>

#include <utility>
#include <unistd.h>


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

    void Button::setFd(int fd) {
        _fd = fd;
    }

    Command::Command(std::string &command) : Action(std::move(command)), _done(true) {}

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

    Macro::Macro(std::string &command,
                 const nlohmann::json &keyMaps) : Action(command) {
        std::string delimiter = "+";
        size_t pos = 0;
        while ((pos = command.find(delimiter)) != std::string::npos) {
            std::string token = command.substr(0, pos);
            command.erase(0, pos + delimiter.length());
            _actionVector.push_back(new Actions::Button(keyMaps.at(token)));
        }
        _actionVector.push_back(new Actions::Button(keyMaps.at(command)));
    }

    void Macro::activate(int16_t) {
        for (auto it: _actionVector) {
            it->activate(1);
            it->deactivate();
        }

    }

    std::vector<Actions::Action *> Macro::getActions() {
        return _actionVector;
    }

    void Macro::deactivate() {

    }
}