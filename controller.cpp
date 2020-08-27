//
// Created by godofall on 23/08/2020.
//
#include "controller.h"
#include <iostream>
#include <fstream>

using namespace std;

/*Controller::Controller() {}
Controller::~Controller() {} */
void Controller::continue_reading() {
    ifstream file ("/dev/hidraw3", ios::in|ios::binary);
    while(file.is_open())
    {
        file.seekg (0, ios::beg);
        file.read (bytes, sizeof(bytes) - 1);
        check_sticks();
    }
    file.close();
}

void Controller::check_buttons(){
    char place_holder = bytes[5];
    for (int i = 0; i < 8; i++) {
        bits[i] = (place_holder & (1 << i)) != 0;
    }
    for (char bit : bits) {
        cout << (int) bit;

    }
    cout << endl;
}
char Controller::absolute(char b){
    b -= 127;
    b = abs(b);
    if(b == -128) b = 127;
    return b;
}

void Controller::check_sticks() {
    is_r3_right = bytes[BYTE_RIGHT_X] & 128;
    is_r3_up = !(bytes[BYTE_RIGHT_Y] & 128);
    is_l3_right = bytes[BYTE_LEFT_X] & 128;
    is_l3_up = !(bytes[BYTE_LEFT_Y] & 128);
    right_stick_x = absolute(bytes[BYTE_RIGHT_X]);
    right_stick_y = absolute(bytes[BYTE_RIGHT_Y]);
    left_stick_x = absolute(bytes[BYTE_LEFT_X]);
    left_stick_y = absolute(bytes[BYTE_LEFT_Y]);
    cout << "L3 X:" <<  (int) left_stick_x << "\tL3 Y:" << (int) left_stick_y;
    cout << "\tL3UP:"<<  is_l3_up << "\tRIGHTRL3:" << is_l3_right;
    cout << "\tR3 X: " << (int) right_stick_x << "\t R3 Y:" << (int) right_stick_y;
    cout << "\tR3UP:" <<  is_r3_up << "\t RIGHTR3:" << is_r3_right;
    cout << endl;
}