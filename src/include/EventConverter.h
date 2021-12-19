//
// Created by godofall on 18/12/2021.
//

#ifndef DUALSHOCKER_EVENTCONVERTER_H
#define DUALSHOCKER_EVENTCONVERTER_H

#include <linux/joystick.h>
#include <unordered_map>
#include <Action.h>
#include <iostream>


class EventClassifier {
public:
    EventClassifier(int eventType, int eventNumber, int eventValue = 0) {
        _eventType = eventType;
        _eventNumber = eventNumber;
        if (eventValue > 1) {
            _eventValue = 3;
        } else if (eventValue < 0) {
            _eventValue = 4;
        } else _eventValue = 0;
    }

    ~EventClassifier() {};

    bool operator==(const EventClassifier &other) const {
        return other.getType() == _eventType && other.getNumber() == _eventNumber && other.getValue() == _eventValue;
    }

    int getType() const {
        return _eventType;
    }

    int getNumber() const {
        return _eventNumber;
    }

    int getValue() const {
        return _eventValue;
    }

private:
    int _eventNumber;
    int _eventType;
    int _eventValue;
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
    explicit EventConverter(std::unordered_map<std::string, Actions::Action *> &eventEventClassifierMap);

    Actions::Action *convert(js_event *event) const;

private:
    std::unordered_map<std::string, Actions::Action *> _eventEventClassifierMap;
    std::unordered_map<EventClassifier, std::string> _eventsNameMap;
};

#endif //DUALSHOCKER_EVENTCONVERTER_H
