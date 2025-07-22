#include "market_data_processor.h"

MarketDataProcessor::MarketDataProcessor() : output_queue(std::make_unique<LockFreeQueue<MarketDataMessage, QUEUE_SIZE>>()) {}

bool MarketDataProcessor::processMessage(const MarketDataMessage& msg) {
    if (last_sequence[msg.instrument_id] >= msg.sequence_number) {
        return false;
    }
    
    if (msg.price <= 0 || msg.price > 1000000) {
        return false;
    }
    
    double last_price = last_prices[msg.instrument_id];
    double price_change = std::abs(msg.price - last_price) / last_price;
    
    if (price_change > 0.10) {
        logPriceAlert(msg);
    }
    
    last_prices[msg.instrument_id] = msg.price;
    last_sequence[msg.instrument_id] = msg.sequence_number;
    
    return output_queue->push(msg);
}

void MarketDataProcessor::logPriceAlert(const MarketDataMessage& msg) {
    // Fast logging without blocking main thread
    // Could use memory-mapped files or async logging
}