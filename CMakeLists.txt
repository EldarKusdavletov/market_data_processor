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
        src/data_sources/DataFeedSimulator.cpp
        src/core/EventType.cpp
        src/core/MarketDataProcessor.cpp
        src/core/MarketEvent.cpp
)

target_include_directories(market_data_lib PUBLIC include)

find_package(Threads REQUIRED)
target_link_libraries(market_data_lib PRIVATE Threads::Threads)

add_executable(market_data_processor main.cpp)
target_link_libraries(market_data_processor PRIVATE market_data_lib)

set_target_properties(market_data_processor PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

option(BUILD_TESTS "Build test programs" ON)

if (BUILD_TESTS)
    enable_testing()

    find_package(GTest QUIET)

    if (NOT GTest_FOUND)
        include(FetchContent)
        FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif ()

    add_executable(market_data_tests tests/test_market_data_processor.cpp)
    target_link_libraries(market_data_tests PRIVATE market_data_lib gtest_main gtest Threads::Threads)

    set_target_properties(market_data_tests PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )

    add_test(NAME MarketDataTests COMMAND market_data_tests)

    include(GoogleTest)
    gtest_discover_tests(market_data_tests)
endif ()


set(CPACK_PACKAGE_NAME "market_data_processor")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_CONTACT "eldar.kusd@gmail.com")

include(CPack)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")