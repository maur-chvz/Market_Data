#include "market_data_cache.h"

void MarketDataCache::updatePrice(const MarketDataMessage& msg) {
    std::unique_lock<std::shared_mutex> lock(cache_mutex);
    
    CacheEntry& entry = cache[msg.instrument_id];
    entry.data = msg;
    // entry.last_updated = getCurrentMicroseconds();
    entry.dirty.store(true);
}

bool MarketDataCache::getLatestPrice(uint32_t instrument_id, MarketDataMessage& msg) {
    std::shared_lock<std::shared_mutex> lock(cache_mutex);
    
    auto it = cache.find(instrument_id);
    if (it != cache.end()) {
        msg = it->second.data;
        return true;
    }
    return false;
}

void MarketDataCache::batchUpdate(const std::vector<MarketDataMessage>& messages) {
    std::unique_lock<std::shared_mutex> lock(cache_mutex);
    
    for (const auto& msg : messages) {
        CacheEntry& entry = cache[msg.instrument_id];
        entry.data = msg;
        // entry.last_updated = getCurrentMicroseconds();
        entry.dirty.store(true);
    }
}