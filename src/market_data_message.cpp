#include "market_data_message.h"

void MarketDataMessage::serialize(char* buffer) const {
    static_assert(std::is_trivially_copyable_v<MarketDataMessage>);
    std::memcpy(buffer, this, sizeof(MarketDataMessage));
}

MarketDataMessage MarketDataMessage::deserialize(const char* buffer) {
    MarketDataMessage msg;
    std::memcpy(&msg, buffer, sizeof(MarketDataMessage));
    return msg;  // RVO eliminates copy
}

void MarketDataMessage::deserialize_inplace(const char* buffer, MarketDataMessage& msg) {
    std::memcpy(&msg, buffer, sizeof(MarketDataMessage));
}