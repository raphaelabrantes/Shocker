//
// Created by godofall on 01/09/2020.
//

#ifndef DUALSHOCKER_EVENTS_H
#define DUALSHOCKER_EVENTS_H

enum buttons{
    SQUARE=0, TRIANGLE, CIRCLE, X, L1, L2, L3, L3_M , R1, R2, R3, R3_L, OPT, SHARE, LEFT_B
};


class Event {
    public:
        Event(int id);
        int get_id();
    private:
        int event_id;
};

class Trigger_Event: public Event{
    public:
        Trigger_Event(int id, unsigned char v);
        unsigned char get_value();
    private:
        unsigned char value;

};

class Stick_Event: public Event{
    public:
        Stick_Event(int id, char x, char y, bool up, bool right);
        bool is_up();
        bool is_right();
        char get_x();
        char get_y();

    private:
        bool up, right;
        char x_axis, y_axis;
};



#endif //DUALSHOCKER_EVENTS_H
