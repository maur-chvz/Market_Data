cmake_minimum_required(VERSION 3.20)
project(MarketData LANGUAGES CXX)

set(SOURCES
    src/market_data.cpp
    src/exchange_connector.cpp
    src/market_data_cache.cpp
    src/market_data_distributor.cpp
    src/market_data_message.cpp
    src/market_data_processor.cpp
    src/market_data_system.cpp
)

set(HEADERS
    src/exchange_connector.h
    src/lock_free_queue.h
    src/market_data_cache.h
    src/market_data_distributor.h
    src/market_data_message.h
    src/market_data_processor.h
    src/market_data_system.h
    src/market_data_util.h
)

add_executable(MarketData ${SOURCES} ${HEADERS})

target_include_directories(MarketData PRIVATE src)

target_compile_features(MarketData PRIVATE cxx_std_20)

set_target_properties(MarketData PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
