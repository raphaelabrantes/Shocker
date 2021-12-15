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
    };

}
#endif //DUALSHOCKER_ACTIONS_H
