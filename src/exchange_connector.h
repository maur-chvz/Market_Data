#ifndef EXCHANGE_CONNECTOR_H
#define EXCHANGE_CONNECTOR_H

#include <iostream>
#include <thread>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// #include "market_data_message.h"
// #include "lock_free_queue.h"

class ExchangeConnector {
private:
    int socket_fd;
    std::string exchange_name;
    std::string exchange_ip;
    int port;
    // LockFreeQueue<MarketDataMessage, 1000000> message_queue;
    std::atomic<bool> running{true};
    std::thread worker_thread;
    
public:
    ExchangeConnector(const std::string& exchange_name, const std::string& exchange_ip, int port);
    ~ExchangeConnector();

    // bool getMessage(MarketDataMessage msg) const; // change later?
    void stop();
private:
    void receiveData();
    void setupSocket();
};

#endif