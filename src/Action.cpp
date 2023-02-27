// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <Action.h>
#include <unistd.h>
#include <utility>
#include <thread>


namespace Actions {
    Action::Action(std::string command) : m_command(std::move(command)) {}

    std::string Action::getCommand() const {
        return m_command;
    }


    Button::Button(int key) : Action(""), m_key(key) {}

    void Button::activate(int16_t) {
        if (!m_isPressed) {
            m_inputEvent.type = EV_KEY;
            m_inputEvent.code = m_key;
            m_inputEvent.value = 1;
            emit();
            sync();
            m_isPressed = true;
        }
    }

    void Button::deactivate() {
        if (m_isPressed) {
            m_inputEvent.type = EV_KEY;
            m_inputEvent.code = m_key;
            m_inputEvent.value = 0;
            emit();
            sync();
            m_isPressed = false;
        }
    }

    void Button::emit() {
        write(m_fd, &m_inputEvent, sizeof(m_inputEvent));
    }

    void Button::sync() {
        m_inputEvent.type = EV_SYN;
        m_inputEvent.code = SYN_REPORT;
        m_inputEvent.value = 0;
        emit();
    }

    int Button::getKey() const {
        return m_key;
    }

    void Button::initiate(int fd) {
        m_fd = fd;
        ioctl(m_fd, UI_SET_KEYBIT, m_key);
    }

    Command::Command(std::string &command) : Action(
            std::move(command)),
            m_done(true) {}

    void Command::activate(int16_t) {
        if (m_done) {
            std::thread thread(&Command::start, this);
            thread.detach();
        }
    }

    void Command::deactivate() {
    }

    void Command::start() {
        m_done = false;
        system(m_command.c_str());
        m_done = true;
    }


    Macro::Macro(std::vector<std::shared_ptr<Actions::Action>> actionVector) :
            m_actionVector(std::move(actionVector)), Action("") {
    }

    Macro::~Macro(){
        m_actionVector.clear();
    }

    void Macro::activate(int16_t) {
        for (auto const &it : m_actionVector) {
            it->activate(1);
            it->deactivate();
        }
    }


    void Macro::initiate(int fd) {
        for (auto const &action : m_actionVector) {
            action->initiate(fd);
        }
    }

    Mouse::Mouse(int key, int sensibility, bool isPositive) :
            Button(key),
            m_sensibility(sensibility),
            m_isPositive(isPositive) {
    }

    void Mouse::activate(int16_t value) {
        m_value = value;
        if (!m_isPressed) {
            m_isPressed = true;
            std::thread mouseThread(&Mouse::start, this);
            mouseThread.detach();
        }
    }

    void Mouse::deactivate() {
        m_isPressed = false;
    }

    void Mouse::start() {
        while (m_isPressed) {
            m_inputEvent.type = EV_REL;
            m_inputEvent.code = getKey();
            __s32 x = m_sensibility * abs(m_value) / 32767;
            m_inputEvent.value = m_isPositive ? x : -x;
            emit();
            sync();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }

    void Mouse::initiate(int fd) {
        m_fd = fd;
        ioctl(m_fd, UI_SET_RELBIT, getKey());
    }


}  // namespace Actions
