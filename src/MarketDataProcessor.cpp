#include <unordered_set>
#include <numeric>
#include <ranges>

#include "../include/MarketDataProcessor.hpp"

void MarketDataProcessor::process_event(const MarketEvent &event) {
    std::unique_lock<std::shared_mutex> lock(mutex_);

    events_.emplace_back(event);

    switch (event.type) {
        case EventType::TRADE:
            handle_trade(event);
            break;
        case EventType::QUOTE:
            handle_quote(event);
            break;
        default:
            std::cout << "Unknown event type: " << event.type << std::endl;
    }

    ++processed_count_;
}

double MarketDataProcessor::get_latest_price(std::string_view symbol) const {
    for (const auto & event : std::ranges::reverse_view(events_)) {
        if (event.symbol == symbol) {
            return event.price;
        }
    }
    return 0.0;
}

int MarketDataProcessor::get_processed_count() const noexcept {
    return processed_count_;
}

const std::vector<MarketEvent> &MarketDataProcessor::get_events() const noexcept {
    return events_;
}

size_t MarketDataProcessor::get_event_count() const noexcept {
    return events_.size();
}

void MarketDataProcessor::print_summary() const {
    std::cout << "\n=== SUMMARY ===" << std::endl;
    std::cout << "Total events processed: " << get_processed_count() << std::endl;

    const std::vector<std::string> symbols = get_unique_symbols();
    for (const auto &symbol: symbols) {
        const double price = get_latest_price(symbol);
        if (price > 0.0) {
            std::cout << symbol << " latest price: $" << price << std::endl;
        }
    }
}

void MarketDataProcessor::clear() noexcept {
    events_.clear();
    processed_count_ = 0;
}

std::vector<std::string> MarketDataProcessor::get_unique_symbols() const {
    std::unordered_set<std::string> unique_symbols;

    for (const auto &event: events_) {
        unique_symbols.insert(event.symbol);
    }

    return std::vector<std::string>(unique_symbols.begin(), unique_symbols.end());
}

double MarketDataProcessor::get_average_price(std::string_view symbol) const {
    std::vector<double> prices;

    for (const auto &event: events_) {
        if (event.symbol == symbol) {
            prices.push_back(event.price);
        }
    }

    if (prices.empty()) {
        return 0.0;
    }

    const double sum = std::accumulate(prices.begin(), prices.end(), 0.0);
    return sum / static_cast<double>(prices.size());
}

void MarketDataProcessor::handle_trade(const MarketEvent &event) {
    std::cout << "[" << event.type << "] " << event.symbol
              << " Price: $" << event.price
              << " Volume: " << event.volume << std::endl;
}

void MarketDataProcessor::handle_quote(const MarketEvent &event) {
    std::cout << "[" << event.type << "] " << event.symbol
              << " Price: $" << event.price << std::endl;
}