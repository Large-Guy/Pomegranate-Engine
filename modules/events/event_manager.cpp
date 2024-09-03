#include "event_manager.h"

std::unordered_map<EventID, std::vector<EventFunction>> Event::_events;
std::unordered_map<std::string, EventID> Event::_eventIndex;
EventID Event::_eventCounter = 0;

void Event::on(EventID id, EventFunction callback) {
    Event::_events[id].push_back(callback);
}

void Event::on(const std::string& name, EventFunction callback) {
    EventID id = Event::getEventId(name);
    Event::_events[id].push_back(callback);
}

EventID Event::createEvent() {
    return Event::_eventCounter++;
}

EventID Event::getEventId(const std::string &name) {
    if(Event::_eventIndex.count(name)) {
        return Event::_eventIndex[name];
    }
    else
    {
        EventID id = Event::createEvent();
        Event::_eventIndex[name] = id;
        return id;
    }
}
