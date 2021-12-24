//
// Created by godofall on 12/12/2021.
//

#ifndef DUALSHOCKER_ACTIONS_H
#define DUALSHOCKER_ACTIONS_H

#include <string>
#include <linux/uinput.h>
#include <thread>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>

namespace Actions {
    class Action {

    public:
        Action(std::string command);

        virtual void activate(int16_t value) = 0;

        virtual void deactivate() = 0;

        std::string getCommand() const;

    protected:
        std::string _command;
    };

    class Button : public Action {
    public:
        Button(int key);

        void activate(int16_t);

        void deactivate();

        void setFd(int fd);

        int getKey() const;

    private:
        void emit();

        void sync();

        input_event _inputEvent;
        int _fd;
        int _key;
        bool _isPressed = false;
    };

    class Command : public Action {
    public:
        Command(std::string &command);

        void activate(int16_t);

        void deactivate();

    private:
        std::atomic<bool> _done;
        std::thread *_thread = nullptr;

        void start();
    };

    class Macro : public Action {
    public:
        Macro(std::string &command,
              const nlohmann::json &keyMaps);

        void activate(int16_t);

        void deactivate();

        std::vector<Action *> getActions();

    private:

        std::vector<Actions::Action *> _actionVector;
    };
}
#endif //DUALSHOCKER_ACTIONS_H
