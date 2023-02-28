//  Copyright (c)  2021-2023.  Raphael Prandini Thomé de Abrantes
//  Use of this source code is governed by an MIT-style
//  license that can be found in the LICENSE file or at
//  https://opensource.org/licenses/MIT.

#pragma once


#include <string>
#include <unordered_map>
#include "Action.h"

namespace Controller {
    class Controller {
    public:
        explicit Controller(std::unordered_map<std::string, std::shared_ptr<Actions::Action>> &actions);

        Actions::Action *at(const std::string &key) const;

        void initiate(int fd);

        ~Controller();

        void stopAll();

    private:
        std::unordered_map<std::string, std::shared_ptr<Actions::Action>> m_actions;
        uinput_setup m_uinputSetup {};
        int m_fd;

    };

    int start_env(Controller &controller,
                  uinput_setup &uinputSetup);
    void stop_env(int fd);

}
