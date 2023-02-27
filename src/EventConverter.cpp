// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <EventConverter.h>


EventConverter::EventConverter(Controller::Controller & controller)
        : m_controller(controller) {
    m_eventsNameMap[EventClassifier(1, 0)] = "X";
    m_eventsNameMap[EventClassifier(1, 1)] = "CIRCLE";
    m_eventsNameMap[EventClassifier(1, 2)] = "TRIANGLE";
    m_eventsNameMap[EventClassifier(1, 3)] = "SQUARE";
    m_eventsNameMap[EventClassifier(1, 4)] = "L1";
    m_eventsNameMap[EventClassifier(1, 5)] = "R1";
    m_eventsNameMap[EventClassifier(1, 6)] = "L2";
    m_eventsNameMap[EventClassifier(1, 7)] = "R2";
    m_eventsNameMap[EventClassifier(1, 8)] = "SHARE";
    m_eventsNameMap[EventClassifier(1, 9)] = "OPT";
    m_eventsNameMap[EventClassifier(1, 10)] = "PS";
    m_eventsNameMap[EventClassifier(1, 11)] = "L3";
    m_eventsNameMap[EventClassifier(1, 12)] = "R3";
    m_eventsNameMap[EventClassifier(2, 0, -1)] = "L3_ML";
    m_eventsNameMap[EventClassifier(2, 0, 3)] = "L3_MR";
    m_eventsNameMap[EventClassifier(2, 1, -1)] = "L3_MU";
    m_eventsNameMap[EventClassifier(2, 1, 3)] = "L3_MD";
    m_eventsNameMap[EventClassifier(2, 2, -1)] = "L2";
    m_eventsNameMap[EventClassifier(2, 2, 3)] = "L2";
    m_eventsNameMap[EventClassifier(2, 3, -1)] = "R3_ML";
    m_eventsNameMap[EventClassifier(2, 3, 3)] = "R3_MR";
    m_eventsNameMap[EventClassifier(2, 4, -1)] = "R3_MU";
    m_eventsNameMap[EventClassifier(2, 4, 3)] = "R3_MD";
    m_eventsNameMap[EventClassifier(2, 5, -1)] = "R2";
    m_eventsNameMap[EventClassifier(2, 5, 3)] = "R2";
    m_eventsNameMap[EventClassifier(2, 6, -1)] = "LEFT_BL";
    m_eventsNameMap[EventClassifier(2, 6, 3)] = "LEFT_BR";
    m_eventsNameMap[EventClassifier(2, 7, -1)] = "LEFT_BU";
    m_eventsNameMap[EventClassifier(2, 7, 3)] = "LEFT_BD";
}

Actions::Action *EventConverter::convert(js_event *event) const {
    EventClassifier eventClassifier(event->type, event->number, event->value);
    return m_controller.at(m_eventsNameMap.at(eventClassifier));
}

void EventConverter::setController(Controller::Controller &controller) {
    controller.stopAll();
    m_controller = controller;


}

void EventConverter::stopAll() {
    m_controller.stopAll();
}
