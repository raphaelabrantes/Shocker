#include "controller.h"


int main () {
    Controller com;
    queue<void *> events;
    while(true){
        this_thread::sleep_for(chrono::microseconds(200));
        events = com.get_events();
        while(!events.empty()){
            Event e = *(Event *) events.front();
            int id = e.get_id();
            if(id < 10){
                cout << "<Event> " << endl;
            }
            else if( 10 <= id && id <= 12){
                cout << "<Trigger Event> ";
                Trigger_Event te = *(Trigger_Event *) events.front();
                cout << "Value: " << (int) te.get_value()<< endl;
            }
            else {
                cout << "<Stick Event> ";
                Stick_Event se = *(Stick_Event *) events.front();
                cout << "Y: " << (int)se.get_y() << " X: " << (int) se.get_x() << " Right: " << (int) se.is_right() << " Up: "
                     << (int) se.is_up()<< endl;
            }
            events.pop();
        }
    }
    return 0;
}