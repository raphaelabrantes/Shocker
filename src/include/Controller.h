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
        explicit Controller(std::unordered_map<std::string, std::shared_ptr<Actions::Action>> &actions) : m_actions(
                std::move(std::move(actions))) {};

        Actions::Action *at(const std::string &key) const{
            return m_actions.at(key).get();
        }

        void initiate(int fd) {
           for (const auto &it : m_actions) {
                it.second->initiate(fd);
            }
        }
        ~Controller() {
            stopAll();
            m_actions.clear();
        }

        void stopAll() {
            for (const auto &item: m_actions){
                item.second->deactivate();
            }
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<Actions::Action>> m_actions;
    };

}
