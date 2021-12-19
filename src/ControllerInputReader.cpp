//
// Created by godofall on 06/11/2021.
//
#include <fstream>
#include "ControllerInputReader.h"
namespace Controller{
    ControllerInputReader::ControllerInputReader(std::string& filename) {
        file = open(filename.c_str(), O_RDONLY);
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
        std::cout << "Error reading file: " << static_cast<int>(bytes) << std::endl;
        exit(-1);
    }
}

