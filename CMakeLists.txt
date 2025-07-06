cmake_minimum_required(VERSION 3.20)

project(market_data_processor
        VERSION 1.0.0
        DESCRIPTION "Market Data Processing System"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wformat=2
        -Wfloat-equal
        -Wconversion
        -Wcast-qual
        -Wcast-align
        -Wmisleading-indentation
        -Wnull-dereference
        -Wdouble-promotion
        -Wimplicit-fallthrough
)

add_library(market_data_lib STATIC)

target_sources(market_data_lib PRIVATE
        src/DataFeedSimulator.cpp
        src/EventType.cpp
        src/MarketDataProcessor.cpp
        src/MarketEvent.cpp
)

target_include_directories(market_data_lib PUBLIC include)

add_executable(market_data_processor main.cpp)
target_link_libraries(market_data_processor PRIVATE market_data_lib)

set(CPACK_PACKAGE_NAME "market_data_processor")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_CONTACT "eldar.kusd@gmail.com")


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")