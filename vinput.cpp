//
// Created by godofall on 08/09/2020.
//

#include "vinput.h"

void emit(int fd, int type, int code, int val)
{
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(fd, &ie, sizeof(ie));
}

void Vinput::key_press(string key){
    emit(fd, EV_KEY, key_codes[key], 1);
    emit(fd, EV_SYN, SYN_REPORT, 0);
    emit(fd, EV_KEY, key_codes[key], 0);
    emit(fd, EV_SYN, SYN_REPORT, 0);

}

void Vinput::init_codes() {
    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    for(auto & key_code : key_codes){
        ioctl(fd, UI_SET_KEYBIT, key_code.second);
    }
    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234; /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
    strcpy(usetup.name, "Virtual Keyboad");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);
    this_thread::sleep_for(chrono::seconds(1));

}
Vinput::~Vinput(){
    this_thread::sleep_for(chrono::seconds(1));
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
}

Vinput::Vinput() {
    ifstream file("../key_codes/keys.k");
    string line, token, key;
    int equal;
    if(file.is_open()){
        while (getline(file, line)){
            equal = line.find('=');
            token = line.substr(0, equal);
            key = line.substr(equal + 1, line.size() -1);
            key_codes[token]  = stoi(key);
        }
        file.close();
        init_codes();
    }
}

