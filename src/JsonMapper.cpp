//0x00
// Created by godofall on 13/12/2021.
//
#include <fstream>
#include <iostream>
#include <JsonMapper.h>


std::unordered_map<std::string, Actions::Action *> JsonMapper::createMapping(const std::string &profile) {

    const nlohmann::json &profileJson = createJsonFromFile(profile);
    const nlohmann::json &keyMaps = createJsonFromFile("key_codes/keys.json");
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


Actions::Action *JsonMapper::createActions(nlohmann::json &json, const nlohmann::json &keymap) {
    auto type = json["type"].get<std::string>();
    auto value = json["value"].get<std::string>();
    if (type == "command") {
        return new Actions::Command(value);
    } else if (type == "button") {
        return new Actions::Button(keymap.at(value).get<int>());
    } else if (type == "mouse") {
        auto sensibility = json["sensibility"].get<int>();
        auto positive = json["positive"].get<bool>();
        return new Actions::Mouse(keymap.at(value).get<int>(), sensibility, positive);
    } else if (type == "macro") {
        return new Actions::Macro(value, keymap);
    }
    std::cout << "Type of action not implemented " << json << std::endl;
    assert(false);
};
