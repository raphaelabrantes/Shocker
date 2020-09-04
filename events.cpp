//
// Created by godofall on 01/09/2020.
//

#include "events.h"

Event::Event(int id) {
    event_id = id;
}

int Event::get_id() {
    return event_id;
}

Trigger_Event::Trigger_Event(int id, unsigned char v):Event(id) {
    value = v;
}
unsigned char Trigger_Event::get_value() {
    return value;
}

Stick_Event::Stick_Event(int id, char x, char y, bool is_up, bool is_right):Event(id) {
    x_axis = x;
    y_axis = y;
    up = is_up;
    right = is_right;
}

bool Stick_Event::is_right() {
    return right;
}

bool Stick_Event::is_up() {
    return up;
}
char Stick_Event::get_x() {
    return x_axis;
}
char Stick_Event::get_y() {
    return y_axis;
}