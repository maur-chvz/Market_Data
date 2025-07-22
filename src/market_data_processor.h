#ifndef MARKET_DATA_PROCESSOR_H
#define MARKET_DATA_PROCESSOR_H

#include <unordered_map>
#include <memory>

#include "market_data_util.h"
#include "market_data_message.h"
#include "lock_free_queue.h"

class MarketDataProcessor {
private:
    std::unordered_map<uint32_t, double> last_prices;
    std::unordered_map<uint32_t, uint32_t> last_sequence;
    std::unique_ptr<LockFreeQueue<MarketDataMessage, QUEUE_SIZE>> output_queue;
    
public:
    MarketDataProcessor();
    bool processMessage(const MarketDataMessage& msg);
    
private:
    void logPriceAlert(const MarketDataMessage& msg);
};

#endif

// multiple queue partitioning?