#pragma once

#include <iostream>

#define EVENT_TYPE_LIST \
    X(TRADE) \
    X(QUOTE)

enum class EventType {
#define X(name) name,
    EVENT_TYPE_LIST
#undef X
};

std::ostream &operator<<(std::ostream &os, EventType type);

bool operator==(EventType type, const std::string &str);

bool operator==(const std::string &str, EventType type);

bool operator!=(EventType type, const std::string &str);

bool operator!=(const std::string &str, EventType type);

EventType from_string(const std::string &str);

extern const EventType all_event_types[];
extern const size_t event_type_count;