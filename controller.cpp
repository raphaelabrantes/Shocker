//
// Created by godofall on 23/08/2020.
//
#include "controller.h"


Controller::Controller() {
    initialization();
    file_reader = thread(&Controller::continue_reading, this);
    file_reader.detach();
 }

 Controller::~Controller() {}

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
    circle = false;
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
        set_events();
        block.unlock();

    }
    cout << "DualShock not connected";
    file.close();
    terminate();
}


void Controller::set_events(){
   if(square){
       auto *e = new Event(SQUARE);
       event_queue.push(e);
   }

   if(triangule) {
       auto *e = new Event(TRIANGLE);
       event_queue.push(e);
   }
   if (circle) {
       auto *e = new Event(CIRCLE);
       event_queue.push(e);
   }
   if(x){
       auto *e = new Event(X);
       event_queue.push(e);
   }
   if(l1) {
       auto *e = new Event(L1);
       event_queue.push(e);
   }
   if(l2) {
       auto *e = new Trigger_Event(L2, l2_trigger);
       event_queue.push(e);
   }
   if(r1){
       auto *e = new Event(R1);
       event_queue.push(e);
   }
   if(r2) {
       auto *e = new Trigger_Event(R2, r2_trigger);
       event_queue.push(e);
   }
   if(opt) {
       auto *e = new Event(OPT);
       event_queue.push(e);
   }
   if(left_buttons  <= 7 ){
       auto *e = new Trigger_Event(LEFT_B, left_buttons);
       event_queue.push(e);
   }
   if((left_stick_y  > 10) || (left_stick_x > 10)) {
       auto *e = new Stick_Event(L3_M, left_stick_x, left_stick_y, is_l3_up, is_l3_right);
       event_queue.push(e);
   }
   if((right_stick_y  > 10) || (right_stick_x > 10)) {
       auto *e = new Stick_Event(R3_M, right_stick_x, right_stick_y, is_r3_up, is_r3_right);
       event_queue.push(e);
   }
   if(share) {
       auto *e = new Event(SHARE);
       event_queue.push(e);
   }
   if(l3) {
       auto *e = new Event(L3);
       event_queue.push(e);
   }
   if(r3) {
       auto *e = new Event(R3);
       event_queue.push(e);
   }
}
queue<void *> Controller::get_events() {
    block.lock();
    queue<void *> temp;
    swap(temp, event_queue);
    block.unlock();
    return temp;
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
    circle = get_bit(bytes[BYTE_BUTTONS], BIT_CIR);
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