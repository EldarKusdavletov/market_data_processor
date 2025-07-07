#include <thread>

#include "core/MarketDataProcessor.hpp"
#include "data_sources/DataFeedSimulator.hpp"

int main() {
    std::cout << "=== Simple Market Data Processor ===" << std::endl;

    MarketDataProcessor processor;
    DataFeedSimulator feed;

    for (int i = 0; i < 20; i++) {
        MarketEvent event = feed.generate_event();
        processor.process_event(event);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    processor.print_summary();
    return 0;
}
