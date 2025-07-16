#ifndef MARKET_DATA_PROCESSOR_H
#define MARKET_DATA_PROCESSOR_H

#include <unordered_map>

#include "market_data_message.h"
#include "lock_free_queue.h"

class MarketDataProcessor {
private:
    std::unordered_map<uint32_t, double> last_prices;
    std::unordered_map<uint32_t, uint32_t> last_sequence;
    LockFreeQueue<MarketDataMessage, 1000000> output_queue;
    
public:
    bool processMessage(const MarketDataMessage& msg);
    
private:
    void logPriceAlert(const MarketDataMessage& msg);
};

#endif

// add macross for the magic numbers...