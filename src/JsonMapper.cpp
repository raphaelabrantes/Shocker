// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <JsonMapper.h>
#include <iostream>
#include <fstream>


std::unordered_map<std::string, Actions::Action *> JsonMapper::createMapping(
        const std::string &profile, const std::string &configPath) {
    const nlohmann::json &profileJson = createJsonFromFile(profile);
    const nlohmann::json &keyMaps = createJsonFromFile(
            configPath + "key_codes/keys.json");
    std::unordered_map<std::string, Actions::Action *> mapping;

    for (auto it = profileJson.begin(); it != profileJson.end(); ++it) {
        auto jsonObj = it->get<nlohmann::json>();
        auto action = createActions(jsonObj, keyMaps);
        mapping[it.key()] = action;
    }
    return mapping;
}


nlohmann::json JsonMapper::createJsonFromFile(const std::string &filePath) {
    std::ifstream jsonFile(filePath);
    if (!jsonFile.is_open()) {
        std::cout << "Failed to open profile file: " << filePath << std::endl;
        exit(1);
    }
    nlohmann::json json;
    jsonFile >> json;
    jsonFile.close();
    return json;
}


Actions::Action *JsonMapper::createActions(const nlohmann::json &json,
                                           const nlohmann::json &keymap) {
    auto type = json["type"].get<std::string>();
    if (type == "command") {
        auto value = json["value"].get<std::string>();
        return new Actions::Command(value);
    } else if (type == "button") {
        auto value = json["value"].get<std::string>();
        return new Actions::Button(keymap.at(value).get<int>());
    } else if (type == "mouse") {
        auto value = json["value"].get<std::string>();
        auto sensibility = json["sensibility"].get<int>();
        auto positive = json["positive"].get<bool>();
        return new Actions::Mouse(
                keymap.at(value).get<int>(),
                sensibility,
                positive);
    } else if (type == "macro") {
        auto value = json["value"].get<nlohmann::json>();
        std::vector<Actions::Action *> macroVec;
        for ( const auto& it : value ) {
            macroVec.push_back(createActions(it, keymap));
        }
        return new Actions::Macro(macroVec);
    }
    std::cout << "Type of action not implemented " << json << std::endl;
    assert(false);
}
