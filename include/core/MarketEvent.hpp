#pragma once

#include "core/EventType.hpp"

struct MarketEvent {
    std::string symbol;
    double price;
    int volume;
    EventType type;

    MarketEvent(std::string sym, double p, int v, EventType t)
        : symbol(std::move(sym)), price(p), volume(v), type(t) {}

    MarketEvent(const MarketEvent &) = default;

    MarketEvent &operator=(const MarketEvent &) = default;

    MarketEvent(MarketEvent &&) = default;

    MarketEvent &operator=(MarketEvent &&) = default;

    ~MarketEvent() = default;

    [[nodiscard]] bool operator==(const MarketEvent &other) const noexcept;

    [[nodiscard]] bool operator!=(const MarketEvent &other) const noexcept;
};