//
// Created by godofall on 23/08/2020.
//
#include "controller.h"


Controller::Controller() {
    initialization();
    file_reader = thread(&Controller::continue_reading, this);
    file_reader.detach();
    while(true){
        block.lock();
        output();
        block.unlock();
        this_thread::sleep_for(chrono::milliseconds(4));

    }
 }

 Controller::~Controller() {

}

void Controller::initialization(){
    left_stick_y = 0;
    left_stick_x = 0;
    right_stick_x = 0;
    right_stick_y = 0;
    left_buttons = 8;
    l2_trigger = 0;
    r2_trigger = 0;
    square = false;
    triangule = false;
    circule = false;
    x = false;
    l1 = false;
    l2 = false;
    l3 = false;
    r1 = false;
    r2 = false;
    r3 = false;
    opt = false;
    share = false;
    is_l3_right = false;
    is_r3_right = false;
    is_l3_up = false;
    is_r3_up = false;
}
void Controller::continue_reading() {
    ifstream file ("/dev/hidraw3", ios::in|ios::binary);
    while(file.is_open())
    {
        file.seekg (0, ios::beg);
        file.read (bytes, sizeof(bytes) - 1);
        block.lock();
        update_inputs();
        block.unlock();

    }
    cout << "DualShock not connected";
    file.close();
    terminate();
}

void Controller::output(){
   if(square) cout << "square " << endl;
   if(triangule) cout << "triangule " << endl;
   if (circule) cout << "circule " << endl;
   if(x) cout << "x " << endl;
   if(l1) cout << "L1 " << endl ;
   if(l2) cout << "L2 " << (int) l2_trigger << endl;
   if(r1) cout << "R1 " << endl;
   if(r2) cout << "R2 "  << (int) r2_trigger << endl;
   if(opt) cout << "OPT" << endl;
   if(left_buttons  <= 7 ) cout << " SETA (0 = ↑) (1 = ↑→) (2 = → ) (3 = ↓→) (4 = ↓) ( 5 = ↓←) (6 = ←) (7 = ↑←)"<< (int) left_buttons << endl;
   if((left_stick_y  > 10) || (left_stick_x > 10)) cout << "L3 X: "<< (int) left_stick_x << " L3 Y: " << (int) left_stick_y << endl;
   if((right_stick_y  > 10) || (right_stick_x > 10)) cout << "R3 X: "<< (int) right_stick_x << " R3 Y: " << (int) right_stick_y << endl;
   if(share) cout << "SHARED " << endl;
   if(l3) cout << "L3 " << endl;
   if(r3) cout << "R3 " << endl;
}

char Controller::absolute(char b){
    b -= 127;
    b = abs(b);
    if(b == -128) b = 127;
    return b;
}

bool Controller::get_bit(char byte, int number){
    return (byte & (1 << number)) != 0;
}

void Controller::update_inputs() {
    is_r3_right = bytes[BYTE_RIGHT_X] & 128;
    is_r3_up = !(bytes[BYTE_RIGHT_Y] & 128);
    is_l3_right = bytes[BYTE_LEFT_X] & 128;
    is_l3_up = !(bytes[BYTE_LEFT_Y] & 128);
    right_stick_x = absolute(bytes[BYTE_RIGHT_X]);
    right_stick_y = absolute(bytes[BYTE_RIGHT_Y]);
    left_stick_x = absolute(bytes[BYTE_LEFT_X]);
    left_stick_y = absolute(bytes[BYTE_LEFT_Y]);
    square = get_bit(bytes[BYTE_BUTTONS], BIT_SQR);
    triangule = get_bit(bytes[BYTE_BUTTONS], BIT_TRI);
    circule = get_bit(bytes[BYTE_BUTTONS], BIT_CIR);
    x = get_bit(bytes[BYTE_BUTTONS], BIT_X);
    l1 = get_bit(bytes[BYTE_SPECIALS], BIT_L1);
    l2 = get_bit(bytes[BYTE_SPECIALS], BIT_L2);
    r1 = get_bit(bytes[BYTE_SPECIALS], BIT_R1);
    r2 = get_bit(bytes[BYTE_SPECIALS], BIT_R2);
    opt = get_bit(bytes[BYTE_SPECIALS], BIT_OPT);
    share = get_bit(bytes[BYTE_SPECIALS], BIT_SHARE);
    r3 = get_bit(bytes[BYTE_SPECIALS], BIT_R3);
    l3 = get_bit(bytes[BYTE_SPECIALS], BIT_L3);
    l2_trigger = bytes[BYTE_L2];
    r2_trigger = bytes[BYTE_R2];
    left_buttons = bytes[BYTE_BUTTONS] & 15;
}