//
// Created by godofall on 08/09/2020.
//

#ifndef DUALSHOCKER_VINPUT_H
#define DUALSHOCKER_VINPUT_H
#include <linux/uinput.h>
#include <map>
#include <string>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include "controller.h"

class Vinput {
public:
    Vinput();
    ~Vinput();
    void key_press(string key);

private:
    struct uinput_setup usetup;
    int fd;
    void init_codes();
    map<std::string, int> key_codes;
};


#endif //DUALSHOCKER_VINPUT_H
