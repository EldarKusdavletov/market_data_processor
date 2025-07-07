#include <chrono>

#include "data_sources/DataFeedSimulator.hpp"

DataFeedSimulator::DataFeedSimulator()
    : symbols_{"AAPL", "GOOGL", "MSFT", "TSLA"}, gen_(std::random_device{}()),
      price_dist_{100.0, 300.0}, volume_dist_{100, 10000}, symbol_dist_{0, static_cast<int>(symbols_.size() - 1)},
      type_dist_{0, static_cast<int>(event_type_count - 1)} {
}

MarketEvent DataFeedSimulator::generate_event() {
    if (symbols_.empty()) {
        throw std::runtime_error("No symbols available for event generation");
    }

    const std::string &symbol = symbols_[static_cast<unsigned long>(symbol_dist_(gen_))];
    const double price = price_dist_(gen_);
    const int volume = volume_dist_(gen_);
    const auto type = static_cast<EventType>(type_dist_(gen_));

    return MarketEvent{symbol, price, volume, type};
}

const std::vector<std::string> &DataFeedSimulator::get_symbols() const noexcept {
    return symbols_;
}

void DataFeedSimulator::add_symbol(const std::string &symbol) {
    if (std::find(symbols_.begin(), symbols_.end(), symbol) == symbols_.end()) {
        symbols_.push_back(symbol);
        symbol_dist_ = std::uniform_int_distribution<>{0, static_cast<int>(symbols_.size() - 1)};
    }
}

void DataFeedSimulator::remove_symbol(const std::string &symbol) {
    auto it = std::find(symbols_.begin(), symbols_.end(), symbol);
    if (it != symbols_.end()) {
        symbols_.erase(it);
        if (!symbols_.empty()) {
            symbol_dist_ = std::uniform_int_distribution<>{0, static_cast<int>(symbols_.size() - 1)};
        }
    }
}