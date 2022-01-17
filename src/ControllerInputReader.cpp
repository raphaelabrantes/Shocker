//
// Created by godofall on 06/11/2021.
//
#include <fstream>
#include "ControllerInputReader.h"
namespace Controller{
    ControllerInputReader::ControllerInputReader(std::string& filename) {
        file = open(filename.c_str(), O_RDONLY);
        if(file < 0) {
            std::cout << "Unable to open joystick file " << filename << std::endl
            << "Check if controller is connected." << std::endl;
            exit(-1);
        }
    }

    ControllerInputReader::~ControllerInputReader(){
       close(file);
    }

    void  ControllerInputReader::getEvent(js_event *event) {
        ssize_t bytes;
        while ((bytes = read(file, event, sizeof(*event))) > 0) {
            if(event->type < JS_EVENT_INIT){
                return;
            }
        }
        std::cout << "Controller Error (disconected): " << static_cast<int>(bytes) << std::endl;
        exit(-1);
    }
}

