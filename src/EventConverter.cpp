//
// Created by godofall on 18/12/2021.
//
#include <EventConverter.h>


EventConverter::EventConverter(std::unordered_map<std::string, Actions::Action *> &eventEventClassifierMap)
        : _eventEventClassifierMap(eventEventClassifierMap) {
    _eventsNameMap[EventClassifier(1, 0)] = "X";
    _eventsNameMap[EventClassifier(1, 1)] = "CIRCLE";
    _eventsNameMap[EventClassifier(1, 2)] = "TRIANGLE";
    _eventsNameMap[EventClassifier(1, 3)] = "SQUARE";
    _eventsNameMap[EventClassifier(1, 4)] = "L1";
    _eventsNameMap[EventClassifier(1, 5)] = "R1";
    _eventsNameMap[EventClassifier(1, 6)] = "L2";
    _eventsNameMap[EventClassifier(1, 7)] = "R2";
    _eventsNameMap[EventClassifier(1, 8)] = "SHARE";
    _eventsNameMap[EventClassifier(1, 9)] = "OPT";
    _eventsNameMap[EventClassifier(1, 10)] = "PS";
    _eventsNameMap[EventClassifier(1, 11)] = "L3";
    _eventsNameMap[EventClassifier(1, 12)] = "R3";
    _eventsNameMap[EventClassifier(2, 0, -1)] = "L3_ML";
    _eventsNameMap[EventClassifier(2, 0, 3)] = "L3_MR";
    _eventsNameMap[EventClassifier(2, 1, -1)] = "L3_MU";
    _eventsNameMap[EventClassifier(2, 1, 3)] = "L3_MD";
    _eventsNameMap[EventClassifier(2, 2, -1)] = "L2";
    _eventsNameMap[EventClassifier(2, 2, 3)] = "L2";
    _eventsNameMap[EventClassifier(2, 3, -1)] = "R3_ML";
    _eventsNameMap[EventClassifier(2, 3, 3)] = "R3_MR";
    _eventsNameMap[EventClassifier(2, 4, -1)] = "R3_MU";
    _eventsNameMap[EventClassifier(2, 4, 3)] = "R3_MD";
    _eventsNameMap[EventClassifier(2, 5, -1)] = "R2";
    _eventsNameMap[EventClassifier(2, 5, 3)] = "R2";
    _eventsNameMap[EventClassifier(2, 6, -1)] = "LEFT_BL";
    _eventsNameMap[EventClassifier(2, 6, 3)] = "LEFT_BR";
    _eventsNameMap[EventClassifier(2, 7, -1)] = "LEFT_BU";
    _eventsNameMap[EventClassifier(2, 7, 3)] = "LEFT_BD";

}

Actions::Action *EventConverter::convert(js_event *event) const {
    EventClassifier eventClassifier(event->type, event->number, event->value);
    return _eventEventClassifierMap.at(_eventsNameMap.at(eventClassifier));
}