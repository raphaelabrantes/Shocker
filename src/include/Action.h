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

        virtual void initiate(int fd) = 0;

    protected:
        std::string _command;
    };

    class Button : public Action {
    public:
        Button(int key);

        void activate(int16_t);

        void deactivate();

        int getKey() const;

        void initiate(int fd);

    protected:
#ifdef emit
#undef emit
        void emit();
#define emit
#else

        void emit();

#endif

        void sync();

        input_event _inputEvent;

    protected:
        int _fd;

    private:
        int _key;
        bool _isPressed = false;
    };

    class Command : public Action {
    public:
        Command(std::string &command);

        ~Command();

        void activate(int16_t);

        void deactivate();

        void initiate(int) {};

    private:
        std::atomic<bool> _done;
        std::thread *_thread = nullptr;

        void start();
    };

    class Macro : public Action {
    public:
        Macro(std::vector<Actions::Action *> actionVector);

        void activate(int16_t);

        void deactivate();

        std::vector<Action *> getActions();

        void initiate(int fd);

    private:

        std::vector<Actions::Action *> _actionVector;
    };

    class Mouse : public Button {
    public:
        Mouse(int key, int sensibility, bool isPositive);

        void activate(int16_t value);

        void deactivate();

        void initiate(int fd);

    private:

        void start();

        int _sensibility;
        bool _isPositive;
        std::thread *_mouseThread = nullptr;
        std::atomic<bool> _isPressed{false};
        std::atomic<int16_t> _value{0};
    };
}
#endif //DUALSHOCKER_ACTIONS_H
