//
// Created by godofall on 01/09/2020.
//

#ifndef DUALSHOCKER_EVENTS_H
#define DUALSHOCKER_EVENTS_H

enum buttons{
    SQUARE, TRIANGLE, CIRCLE, X, L1, L3, R1, R3, OPT, SHARE, L2, R2, LEFT_B, L3_M, R3_M
};

enum directions{
    LEFT_BU=12, LEFT_BR, LEFT_BL,
    LEFT_BD, L3_MU, L3_MR, L3_ML, L3_MD, R3_MU, R3_MR, R3_ML, R3_MD,
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
