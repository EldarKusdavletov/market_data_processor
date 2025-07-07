#include <thread>

#include <gtest/gtest.h>

#include "core/MarketDataProcessor.hpp"

class MarketDataProcessorTest : public ::testing::Test {
protected:
    void SetUp() override {
        processor = std::make_unique<MarketDataProcessor>();
    }

    void TearDown() override {
        processor.reset();
    }

    std::unique_ptr<MarketDataProcessor> processor;
};

TEST_F(MarketDataProcessorTest, ConcurrentProcessing) {
    const int numThreads = 4;
    const int eventsPerThread = 100;
    std::vector<std::thread> threads;

    threads.reserve(numThreads);
    for (int t = 0; t < numThreads; ++t) {
        threads.emplace_back([this, t]() {
            for (int i = 0; i < eventsPerThread; ++i) {
                MarketEvent event = MarketEvent("SYMBOL " + std::to_string(t), 100.0 + i, 1000 + i, EventType::TRADE);
                processor->process_event(event);
            }
        });
    }

    for (auto &thread: threads) {
        thread.join();
    }

    SUCCEED();
}