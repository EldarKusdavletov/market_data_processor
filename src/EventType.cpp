#include "EventType.hpp"

std::ostream &operator<<(std::ostream &os, EventType type) {
    switch (type) {
#define X(name) case EventType::name: os << #name; break;
        EVENT_TYPE_LIST
#undef X
        default:
            throw std::invalid_argument("Invalid EventType");
    }
    return os;
}

bool operator==(EventType type, const std::string &str) {
    switch (type) {
#define X(name) case EventType::name: return str == #name;
        EVENT_TYPE_LIST
#undef X
    }
    return false;
}

bool operator==(const std::string &str, EventType type) {
    return type == str;
}

bool operator!=(EventType type, const std::string &str) {
    return !(type == str);
}

bool operator!=(const std::string &str, EventType type) {
    return !(str == type);
}

EventType from_string(const std::string &str) {
#define X(name) if (str == #name) return EventType::name;
    EVENT_TYPE_LIST
#undef X
    throw std::invalid_argument("Invalid EventType string: " + str);
}

const EventType all_event_types[] = {
#define X(name) EventType::name,
    EVENT_TYPE_LIST
#undef X
};

const size_t event_type_count = sizeof(all_event_types) / sizeof(all_event_types[0]);