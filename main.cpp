#include <thread>

#include "include/MarketDataProcessor.hpp"
#include "include/DataFeedSimulator.hpp"

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
