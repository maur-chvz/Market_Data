#ifndef MARKET_DATA_MESSAGE_H
#define MARKET_DATA_MESSAGE_H

#include <cstdint>
#include <unordered_set>

struct MarketDataMessage {
    uint64_t timestamp;
    uint32_t instrument_id;
    double price;
    uint64_t volume;
    char side;
    uint32_t sequence_number;
    
    void serialize(char* buffer) const;
    static MarketDataMessage deserialize(const char* buffer);
};

struct Subscription {
    uint32_t client_id;
    std::unordered_set<uint32_t> instrument_ids;
    bool full_market;
    double price_threshold;
};

#endif