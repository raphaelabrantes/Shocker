#include "controller.h"


int main () {
    Controller com;
    queue<void *> events;
    while(true){
        events = com.get_events();
        while(!events.empty()){
            Event e = *(Event *) events.front();
            if(e.get_id() > 16 || e.get_id() < 0){
                Trigger_Event e = *(Trigger_Event *) events.front();
            }
            cout << e.get_id();
             events.pop();
        }
    }
    return 0;
}