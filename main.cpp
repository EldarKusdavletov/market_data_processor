#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ranges>
#include <thread>
#include <chrono>

#define EVENT_TYPE_LIST \
    X(TRADE) \
    X(QUOTE)

enum class EventType {
#define X(name) name,
    EVENT_TYPE_LIST
#undef X
};

//std::string to_string(EventType type) {
//    switch (type) {
//#define X(name) case EventType::name: return #name;
//        EVENT_TYPE_LIST
//#undef X
//    }
//    throw std::invalid_argument("Invalid EventType");
//}
//
//EventType from_string(const std::string &str) {
//#define X(name) if (str == #name) return EventType::name;
//    EVENT_TYPE_LIST
//#undef X
//    throw std::invalid_argument("Invalid EventType string: " + str);
//}

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

//constexpr EventType all_event_types[] = {
//#define X(name) EventType::name,
//    EVENT_TYPE_LIST
//#undef X
//};

struct MarketEvent {
    std::string symbol;
    double price;
    int volume;
    EventType type;

    MarketEvent(const std::string &sym, double p, int v, const EventType &t)
        : symbol(sym), price(p), volume(v), type(t) {}
};

// Market Data Processor
class MarketDataProcessor {
private:
    std::vector<MarketEvent> events;
    int processed_count = 0;

public:
    void process_event(const MarketEvent &event) {
        events.emplace_back(event);

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

        processed_count++;
    }

    static void handle_trade(const MarketEvent &event) {
        std::cout << "[" << event.type << "] " << event.symbol
                  << " Price: $" << event.price
                  << " Volume: " << event.volume << std::endl;
    }

    static void handle_quote(const MarketEvent &event) {
        std::cout << "[" << event.type << "] " << event.symbol
                  << " Price: $" << event.price << std::endl;
    }

    double get_latest_price(const std::string &symbol) {
        for (const auto &event: std::ranges::reverse_view(events)) {
            if (event.symbol == symbol) {
                return event.price;
            }
        }
        return 0.0;
    }

    [[nodiscard]] int get_processed_count() const {
        return processed_count;
    }

    void print_summary() {
        std::cout << "\n=== SUMMARY ===" << std::endl;
        std::cout << "Total events processed: " << get_processed_count() << std::endl;

        std::vector<std::string> symbols = {"AAPL", "GOOGL", "MSFT"};
        for (const auto &symbol: symbols) {
            double price = get_latest_price(symbol);
            if (price > 0) {
                std::cout << symbol << " latest price: $" << price << std::endl;
            }
        }
    }
};

class DataFeedSimulator {
private:
    std::vector<std::string> symbols = {"AAPL", "GOOGL", "MSFT", "TSLA"};
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> price_dist;
    std::uniform_int_distribution<> volume_dist;
    std::uniform_int_distribution<> symbol_dist;
    std::uniform_int_distribution<> type_dist;

public:
    DataFeedSimulator() : gen(rd()), price_dist(100.0, 300.0),
                          volume_dist(100, 10000), symbol_dist(0, 3), type_dist(0, 1) {}

    MarketEvent generate_event() {
        std::string symbol = symbols[symbol_dist(gen)];
        double price = price_dist(gen);
        int volume = volume_dist(gen);
        EventType type = (type_dist(gen) == 0) ? EventType::TRADE : EventType::QUOTE;

        return MarketEvent({symbol, price, volume, type});
    }
};

int main() {
    std::cout << "=== Simple Market Data Processor ===" << std::endl;

    MarketDataProcessor processor;
    DataFeedSimulator feed;

    for (int i = 0; i < 20; i++) {
        MarketEvent event = feed.generate_event();
        processor.process_event(event);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    processor.print_summary();
    return 0;
}
