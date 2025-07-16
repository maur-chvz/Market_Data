#ifndef MARKET_DATA_CACHE_H
#define MARKET_DATA_CACHE_H

#include <cstdint>
#include <atomic>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>

#include "market_data_message.h"

class MarketDataCache {
private:
    struct CacheEntry {
        MarketDataMessage data;
        uint64_t last_updated;
        std::atomic<bool> dirty{false};
    };
    
    std::unordered_map<uint32_t, CacheEntry> cache;
    std::shared_mutex cache_mutex;
    
public:
    void updatePrice(const MarketDataMessage& msg);
    bool getLatestPrice(uint32_t instrument_id, MarketDataMessage& msg);
    void batchUpdate(const std::vector<MarketDataMessage>& messages);
};

#endif