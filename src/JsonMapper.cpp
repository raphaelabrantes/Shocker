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

    for (auto it = profileJson.begin(); it != profileJson.end(); ++it) {
        std::string value(it.value().get<std::string>());
        if (value.find(command) != std::string::npos) {
            assert(false);
        } else {
            std::cout << " Key: " << it.key() << " Value: " << value << " keymapsAT: " << keyMaps.at(value)
                      << std::endl;
            auto *action = new Actions::Button(keyMaps.at(value));
            mapping[it.key()] = action;
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
