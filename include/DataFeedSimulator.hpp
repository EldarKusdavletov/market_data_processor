#pragma once

#include <random>

#include "MarketEvent.hpp"

class DataFeedSimulator {
private:
    std::vector<std::string> symbols_;
    std::mt19937 gen_;
    std::uniform_real_distribution<> price_dist_;
    std::uniform_int_distribution<> volume_dist_;
    std::uniform_int_distribution<> symbol_dist_;
    std::uniform_int_distribution<> type_dist_;

public:
    DataFeedSimulator();

    DataFeedSimulator(const DataFeedSimulator &) = delete;

    DataFeedSimulator &operator=(const DataFeedSimulator &) = delete;

    DataFeedSimulator(DataFeedSimulator &&) = default;

    DataFeedSimulator &operator=(DataFeedSimulator &&) = default;

    ~DataFeedSimulator() = default;

    [[nodiscard]] MarketEvent generate_event();

    [[nodiscard]] const std::vector<std::string> &get_symbols() const noexcept;

    void add_symbol(const std::string &symbol);

    void remove_symbol(const std::string &symbol);
};