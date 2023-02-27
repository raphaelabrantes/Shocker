//  Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
//  Use of this source code is governed by an MIT-style
//  license that can be found in the LICENSE file or at
//  https://opensource.org/licenses/MIT.

#pragma once

#include <string>
#include <linux/uinput.h>
#include <atomic>
#include <vector>
#include <memory>
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
        std::string m_command;
    };

    class Button : public Action {
    public:
        explicit Button(int key);

        void activate(int16_t) override;

        void deactivate() override;

        [[nodiscard]] int getKey() const;

        void initiate(int fd) override;

    protected:
        void emit();

        void sync();

        input_event m_inputEvent;

        int m_fd;

    private:
        int m_key;
        bool m_isPressed = false;
    };

    class Command : public Action {
    public:
        explicit Command(std::string &command);

        void activate(int16_t) override;

        void deactivate() override;

        void initiate(int) override {};

    private:
        std::atomic<bool> m_done;
        void start();
    };

    class Macro : public Action {
    public:
        explicit Macro(std::vector<std::shared_ptr<Actions::Action>> actionVector);

        void activate(int16_t) override;

        void deactivate() override {};

        void initiate(int fd) override;

        ~Macro();

    private:
        std::vector<std::shared_ptr<Actions::Action>> m_actionVector;
    };

    class Mouse : public Button {
    public:
        Mouse(int key, int sensibility, bool isPositive);

        void activate(int16_t value) override;

        void deactivate() override;

        void initiate(int fd) override;

    private:

        void start();

        int m_sensibility;
        bool m_isPositive;
        std::atomic<bool> m_isPressed{false};
        std::atomic<int16_t> m_value{0};
    };
}
#ifdef EMIT_DEFINED
#define emit
#undef EMIT_DEFINED
#endif