//
// Created by godofall on 06/09/2020.
//

#ifndef DUALSHOCKER_PARSER_H
#define DUALSHOCKER_PARSER_H
#include "controller.h"
#include <map>

class Parser {
public:
    map<int, string> get_key_maps(const string &filename);

private:
    bool check_valid(string t, int type);
    string match_tokens[25] = {"square", "triangle", "circle", "X", "L1", "L3", "R1", "R3", "opt", "share", "L2", "R2",
                               "LEFT_BU", "LEFT_BR", "LEFT_BL", "LEFT_BD", "L3_MU", "L3_MR", "L3_ML", "L3_MD", "R3_MU",
                               "R3_MR", "R3_ML", "R3_MD"};
    map<int, string> key_maps;

};


#endif //DUALSHOCKER_PARSER_H
