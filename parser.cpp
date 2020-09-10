//
// Created by godofall on 06/09/2020.
//
#include "parser.h"

bool Parser::check_valid(string t, int type){
    return (t == match_tokens[type] && !key_maps.count(type));
}

map<int, string> Parser::get_key_maps(const string& filename){
    ifstream file(filename);
    if(file.is_open()){
        string line, token, key;
        int number = 0;
        while(getline(file, line)){
            number++;
            int equal_signal = line.find('=');
            token=line.substr(0, equal_signal);
            key=line.substr(equal_signal+1, line.size() -1);

            if(check_valid(token,  SQUARE))        key_maps[SQUARE] = key;
            else if(check_valid(token,  TRIANGLE)) key_maps[TRIANGLE] = key;
            else if(check_valid(token,  CIRCLE))   key_maps[CIRCLE] = key;
            else if(check_valid(token,  X))        key_maps[X] = key;
            else if(check_valid(token,  L1))       key_maps[L1] = key;
            else if(check_valid(token,  L3))       key_maps[L3] = key;
            else if(check_valid(token,  R1))       key_maps[R1] = key;
            else if(check_valid(token,  R3))       key_maps[R3] = key;
            else if(check_valid(token,  OPT))      key_maps[OPT] = key;
            else if(check_valid(token,  SHARE))    key_maps[SHARE] = key;
            else if(check_valid(token,  L2))       key_maps[L2] = key;
            else if(check_valid(token,  R2))       key_maps[R2] = key;
            else if(check_valid(token,  LEFT_BU))  key_maps[LEFT_BU] = key;
            else if(check_valid(token,  LEFT_BR))  key_maps[LEFT_BR] = key;
            else if(check_valid(token,  LEFT_BL))  key_maps[LEFT_BL] = key;
            else if(check_valid(token,  LEFT_BD))  key_maps[LEFT_BD] = key;
            else if(check_valid(token,  L3_MU))    key_maps[L3_MU] = key;
            else if(check_valid(token,  L3_MR))    key_maps[L3_MR] = key;
            else if(check_valid(token,  L3_ML))    key_maps[L3_ML] = key;
            else if(check_valid(token,  L3_MD))    key_maps[L3_MD] = key;
            else if(check_valid(token,  R3_MU))    key_maps[R3_MU] = key;
            else if(check_valid(token,  R3_MR))    key_maps[R3_MR] = key;
            else if(check_valid(token,  R3_ML))    key_maps[R3_ML] = key;
            else if(check_valid(token,  R3_MD))    key_maps[R3_MD] = key;
            else{
                cout << "Error in the configuration file " << token << "in the line " << number<< endl ;
                exit(-10);
            }
        }
        file.close();
        return key_maps ;
    }
    else cout << "File: '" << filename <<"' Does not exists";
    exit(-30);
}
#include "parser.h"
