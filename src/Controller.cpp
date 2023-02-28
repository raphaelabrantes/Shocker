//
// Created by godofall on 28/02/23.
//

#include <Controller.h>
#include <linux/uinput.h>
#include <fcntl.h>
#include <Exception.h>
#include <csignal>
#include <cstring>

Controller::Controller::Controller(std::unordered_map<std::string, std::shared_ptr<Actions::Action>> &actions) :
        m_actions(std::move(actions)) {
    m_fd = start_env(*this, m_uinputSetup);

}

Actions::Action *Controller::Controller::at(const std::string &key) const {
    return m_actions.at(key).get();
}

void Controller::Controller::initiate(int fd) {
    for (const auto &it: m_actions) {
        it.second->initiate(fd);
    }
}

Controller::Controller::~Controller() {
    stopAll();
    m_actions.clear();
    stop_env(m_fd);
}

void Controller::Controller::stopAll() {
    for (const auto &item: m_actions) {
        item.second->deactivate();
    }
}

int Controller::start_env(Controller &controller, uinput_setup &uinputSetup) {
    std::cout << "Creating device" << std::endl;
    int fd = open("/dev/uinput",
                  O_WRONLY | O_NONBLOCK);
    if (fd < 0) {
        std::cout << "It was not possible to"
                     " create the keyboard and mouse device" << std::endl;
        throw UnableToCreateVirtualDevice();
    }
    ioctl(fd, UI_SET_EVBIT, EV_REL);
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);
    controller.initiate(fd);
    memset(&uinputSetup, 0, sizeof(uinputSetup));
    uinputSetup.id.bustype = BUS_USB;
    uinputSetup.id.vendor = 0x1234;
    uinputSetup.id.product = 0x5678;
    strcpy(uinputSetup.name, "Shocker Keyboard and Mouse");
    ioctl(fd, UI_DEV_SETUP, &uinputSetup);
    ioctl(fd, UI_DEV_CREATE);
    return fd;

}

void Controller::stop_env(int fd){
    std::cout << "Deleting device" << std::endl;
    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
}
