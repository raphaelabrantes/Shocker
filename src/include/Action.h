//
// Created by godofall on 12/12/2021.
//

#ifndef DUALSHOCKER_ACTIONS_H
#define DUALSHOCKER_ACTIONS_H

#include <string>
#include <linux/uinput.h>

namespace Actions {
    class Action {

    public:
        Action(std::string command);

        virtual void activate() = 0;

        virtual void deactivate() = 0;

    protected:
        std::string _command;

    };

    class Button : Action {
    public:
        Button(const std::string &key, int fd);

        void activate();

        void deactivate();

    private:
        void emit();

        void sync();

        input_event _inputEvent;
        int _fd;
        int _key;
    };

}
#endif //DUALSHOCKER_ACTIONS_H
