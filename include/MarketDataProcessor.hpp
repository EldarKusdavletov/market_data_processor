#pragma once

#include "MarketEvent.hpp"
#include <vector>

class MarketDataProcessor {
private:
    std::vector<MarketEvent> events_;
    int processed_count_ = 0;

public:
    MarketDataProcessor() = default;

    MarketDataProcessor(const MarketDataProcessor &) = delete;

    MarketDataProcessor &operator=(const MarketDataProcessor &) = delete;

    MarketDataProcessor(MarketDataProcessor &&) = default;

    MarketDataProcessor &operator=(MarketDataProcessor &&) = default;

    ~MarketDataProcessor() = default;

    void process_event(const MarketEvent &event);

    [[nodiscard]] double get_latest_price(std::string_view symbol) const;

    [[nodiscard]] int get_processed_count() const noexcept;

    [[nodiscard]] const std::vector<MarketEvent> &get_events() const noexcept;

    [[nodiscard]] size_t get_event_count() const noexcept;

    void print_summary() const;

    void clear() noexcept;

    [[nodiscard]] std::vector<std::string> get_unique_symbols() const;

    [[nodiscard]] double get_average_price(std::string_view symbol) const;

private:
    static void handle_trade(const MarketEvent &event);

    static void handle_quote(const MarketEvent &event);
};