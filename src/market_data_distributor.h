#ifndef MARKET_DATA_DISTRIBUTOR_H
#define MARKET_DATA_DISTRIBUTOR_H

#include <vector>
#include <cstdint>
#include <unordered_map>
#include <thread>
#include <unordered_set>
#include <sys/socket.h>

#include "market_data_message.h"

class MarketDataDistributor {
private:
    std::vector<Subscription> subscriptions;
    std::unordered_map<uint32_t, int> client_sockets;
    std::thread distribution_thread;
    
public:
    void subscribe(uint32_t client_id, const std::vector<uint32_t>& instruments);
    void distributeMessage(const MarketDataMessage& msg);
    
private:
    bool shouldSendToClient(const Subscription& sub, const MarketDataMessage& msg);
    void sendToClient(uint32_t client_id, const char* data, size_t size);
    void handleSlowClient(uint32_t client_id);
};

#endif

