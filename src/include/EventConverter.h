// Copyright (c)  2021-2022.  Raphael Prandini Thomé de Abrantes
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#pragma once

#include <linux/joystick.h>
#include <unordered_map>
#include <Action.h>
#include <iostream>
#include "Controller.h"


class EventClassifier {
public:
    EventClassifier(int eventType, int eventNumber, int eventValue = 0) {
        m_eventType = eventType;
        m_eventNumber = eventNumber;
        if (eventValue > 1) {
            m_eventValue = 3;
        } else if (eventValue < 0) {
            m_eventValue = 4;
        } else m_eventValue = 0;
    }

    ~EventClassifier() = default;

    bool operator==(const EventClassifier &other) const {
        return other.getType() == m_eventType && other.getNumber() == m_eventNumber && other.getValue() == m_eventValue;
    }

    int getType() const {
        return m_eventType;
    }

    int getNumber() const {
        return m_eventNumber;
    }

    int getValue() const {
        return m_eventValue;
    }

private:
    int m_eventNumber;
    int m_eventType;
    int m_eventValue;
};

namespace std {
    template<>
    struct hash<EventClassifier> {
        std::size_t operator()(const EventClassifier &eventClassifier) const {
            uint64_t result = 1000 * eventClassifier.getType() + eventClassifier.getNumber() * 100 +
                              eventClassifier.getValue() * 1;
            return std::hash<uint64_t>()(result);
        }
    };
}

class EventConverter {
public:
    explicit EventConverter(Controller::Controller &controller);
    Actions::Action *convert(js_event *event) const;
    void setController(Controller::Controller &controller);
    void stopAll();
private:
    Controller::Controller m_controller;
    std::unordered_map<EventClassifier, std::string> m_eventsNameMap;
};

