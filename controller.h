#ifndef DUALSHOCKER_CONTROLLER_H
#define DUALSHOCKER_CONTROLLER_H
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
#include <chrono>
#define BYTE_L2 8
#define BYTE_R2 9
#define BYTE_SPECIALS 6
#define BYTE_BUTTONS 5
#define BYTE_RIGHT_Y 4
#define BYTE_RIGHT_X 3
#define BYTE_LEFT_Y 2
#define BYTE_LEFT_X 1
#define BIT_TRI 7
#define BIT_R3 7
#define BIT_CIR 6
#define BIT_L3 6
#define BIT_X 5
#define BIT_OPT 5
#define BIT_SQR 4
#define BIT_SHARE 4
#define BIT_R2 3
#define BIT_L2 2
#define BIT_R1 1
#define BIT_L1 0
using namespace std;

class Controller {
public:
    Controller();
    ~Controller();
    void continue_reading();
    void update_inputs();
    void initialization();
    void output();

private:
    char bytes [64] = {0}, bits[8], left_stick_x, left_stick_y, right_stick_x, right_stick_y;
    char absolute(char b);
    thread file_reader;
    mutex block;
    bool square, triangule, circule, x, l1, l2, r1, r2, opt, share ,is_r3_right, is_r3_up, is_l3_right, is_l3_up, l3, r3;
    unsigned char left_buttons,  l2_trigger, r2_trigger;
    bool get_bit(char byte, int place);
};


#endif //DUALSHOCKER_CONTROLLER_H
