#include "market_data_distributor.h"

void MarketDataDistributor::subscribe(uint32_t client_id, const std::vector<uint32_t>& instruments) {
    Subscription sub;
    sub.client_id = client_id;
    sub.instrument_ids = std::unordered_set<uint32_t>(instruments.begin(), instruments.end());
    sub.full_market = false;
    subscriptions.push_back(sub);
}

void MarketDataDistributor::distributeMessage(const MarketDataMessage& msg) {
    char serialized_msg[256];
    msg.serialize(serialized_msg);
    
    for (const auto& sub : subscriptions) {
        if (shouldSendToClient(sub, msg)) {
            sendToClient(sub.client_id, serialized_msg, sizeof(serialized_msg));
        }
    }
}

bool MarketDataDistributor::shouldSendToClient(const Subscription& sub, const MarketDataMessage& msg) {
    return sub.full_market || sub.instrument_ids.count(msg.instrument_id) > 0;
}

void MarketDataDistributor::sendToClient(uint32_t client_id, const char* data, size_t size) {
    int socket_fd = client_sockets[client_id];
    
    int flags = MSG_DONTWAIT;
    ssize_t sent = send(socket_fd, data, size, flags);
    
    if (sent == -1 && errno == EAGAIN) {
        handleSlowClient(client_id);
    }
}

void MarketDataDistributor::handleSlowClient(uint32_t client_id) {
    // Implement conflation or disconnect slow clients
    // This prevents one slow client from affecting others
}