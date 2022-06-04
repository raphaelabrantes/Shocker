//
// Created by godofall on 12/12/2021.
//

#pragma once

#include <string>
#include <linux/uinput.h>
#include <thread>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>

#ifdef emit
#undef emit
#define EMIT_DEFINED
#endif

namespace Actions {
    class Action {

    public:
        explicit Action(std::string command);

        virtual void activate(int16_t value) = 0;

        virtual void deactivate() = 0;

        std::string getCommand() const;

        virtual void initiate(int fd) = 0;

    protected:
        std::string _command;
    };

    class Button : public Action {
    public:
        explicit Button(int key);

        void activate(int16_t) override;

        void deactivate() override;

        int getKey() const;

        void initiate(int fd) override;

    protected:
        void emit();

        void sync();

        input_event _inputEvent;

        int _fd;

    private:
        int _key;
        bool _isPressed = false;
    };

    class Command : public Action {
    public:
        explicit Command(std::string &command);

        ~Command();

        void activate(int16_t) override;

        void deactivate() override;

        void initiate(int) override {};

    private:
        std::atomic<bool> _done;
        std::thread *_thread = nullptr;

        void start();
    };

    class Macro : public Action {
    public:
        explicit Macro(std::vector<Actions::Action *> actionVector);

        void activate(int16_t) override;

        void deactivate() override;

        std::vector<Action *> getActions() const;

        void initiate(int fd) override;

    private:

        std::vector<Actions::Action *> _actionVector;
    };

    class Mouse : public Button {
    public:
        Mouse(int key, int sensibility, bool isPositive);

        void activate(int16_t value) override;

        void deactivate() override;

        void initiate(int fd) override;

    private:

        void start();

        int _sensibility;
        bool _isPositive;
        std::thread *_mouseThread = nullptr;
        std::atomic<bool> _isPressed{false};
        std::atomic<int16_t> _value{0};
    };
}
#ifdef EMIT_DEFINED
#define emit
#undef EMIT_DEFINED
#endif