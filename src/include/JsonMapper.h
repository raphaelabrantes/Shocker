//
// Created by godofall on 13/12/2021.
//

#pragma once
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <Action.h>

class JsonMapper {
public:
    static std::unordered_map<std::string, Actions::Action *> createMapping(const std::string &profile);
private:
    static nlohmann::json createJsonFromFile(const std::string &filePath);

    static Actions::Action *createActions(nlohmann::json &json, const nlohmann::json &keymap);
};


