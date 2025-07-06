#include "../include/MarketEvent.hpp"

bool MarketEvent::operator==(const MarketEvent &other) const noexcept {
    return symbol == other.symbol &&
           std::abs(price - other.price) < 1e-9 &&
           volume == other.volume &&
           type == other.type;
}

bool MarketEvent::operator!=(const MarketEvent &other) const noexcept {
    return !(*this == other);
}