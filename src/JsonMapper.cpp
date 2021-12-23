//
// Created by godofall on 13/12/2021.
//
#include <fstream>
#include <iostream>
#include <JsonMapper.h>


std::unordered_map<std::string, Actions::Action *> JsonMapper::createMapping(const std::string &profile) {
    const nlohmann::json &profileJson = createJsonFromFile(profile);
    const nlohmann::json &keyMaps = createJsonFromFile("key_codes/keys.json");
    std::unordered_map<std::string, Actions::Action *> mapping;
    std::string command("command");
    std::string button("button");

    for (auto it = profileJson.begin(); it != profileJson.end(); ++it) {
        if (it->contains(command)) {
            auto value = it->at(command).get<std::string>();
            auto *action = new Actions::Command(value);
            mapping[it.key()] = action;

        } else if (it->contains(button)) {
            auto value = it->at(button).get<std::string>();
            auto *action = new Actions::Button(keyMaps.at(value));
            mapping[it.key()] = action;

        } else {
            std::cout << "Not implemented " << it.value() << std::endl;
            assert(false);
        }
    }
    return mapping;
}


nlohmann::json JsonMapper::createJsonFromFile(const std::string &filePath) {
    std::ifstream jsonFile(filePath);
    if (!jsonFile.is_open()) {
        std::cout << "Failed to open json file: " << filePath << std::endl;
        exit(1);
    }
    nlohmann::json json;
    jsonFile >> json;
    jsonFile.close();
    return json;
}
