// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <iostream>
#include <fstream>
#include <memory>
#include <JsonMapper.h>
#include <Exception.h>

std::unordered_map<std::string, std::shared_ptr<Actions::Action>> JsonMapper::createMapping(
        const std::string &profile, const std::string &configPath) {
    const nlohmann::json &profileJson = createJsonFromFile(profile);
    const nlohmann::json &keyMaps = createJsonFromFile(
            configPath + "key_codes/keys.json");
    std::unordered_map<std::string, std::shared_ptr<Actions::Action>> mapping;

    for (auto it = profileJson.begin(); it != profileJson.end(); ++it) {
        auto jsonObj = it->get<nlohmann::json>();
        mapping[it.key()] = std::move(createActions(jsonObj, keyMaps));
    }
    return mapping;
}


nlohmann::json JsonMapper::createJsonFromFile(const std::string &filePath) {
    std::ifstream jsonFile(filePath);
    if (!jsonFile.is_open()) {
        std::cout << "Failed to open profile file: " << filePath << std::endl;
        throw FileNotFound(filePath);
    }
    nlohmann::json json;
    jsonFile >> json;
    jsonFile.close();
    return json;
}


std::shared_ptr<Actions::Action> JsonMapper::createActions(const nlohmann::json &json,
                                           const nlohmann::json &keymap) {
    auto type = json["type"].get<std::string>();
    if (type == "command") {
        auto value = json["value"].get<std::string>();
        return std::make_shared<Actions::Command>(value);
    } else if (type == "button") {
        auto value = json["value"].get<std::string>();
        return std::make_shared<Actions::Button>(keymap.at(value).get<int>());
    } else if (type == "mouse") {
        auto value = json["value"].get<std::string>();
        auto sensibility = json["sensibility"].get<int>();
        auto positive = json["positive"].get<bool>();
        return std::make_shared<Actions::Mouse>(
                keymap.at(value).get<int>(),
                sensibility,
                positive);
    } else if (type == "macro") {
        auto value = json["value"].get<nlohmann::json>();
        std::vector<std::shared_ptr<Actions::Action>> macroVec;
        for (const auto &it : value) {
            macroVec.push_back(std::move(createActions(it, keymap)));
        }
        return std::make_shared<Actions::Macro>(std::move(macroVec));
    }
    std::cout << "Type of action not implemented " << json << std::endl;
    assert(false);
}
