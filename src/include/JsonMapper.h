// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include <Action.h>

class JsonMapper {
 public:
    static std::unordered_map<std::string, std::shared_ptr<Actions::Action>> createMapping(
            const std::string &profile, const std::string &configPath);

 private:
    static nlohmann::json createJsonFromFile(const std::string &filePath);

    static std::shared_ptr<Actions::Action> createActions(const nlohmann::json &json,
                                          const nlohmann::json &keymap);
};


