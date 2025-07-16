#ifndef MARKET_DATA_SYSTEM_H
#define MARKET_DATA_SYSTEM_H

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <string>

#include "exchange_connector.h"
#include "market_data_processor.h"
// #include "market_data_distributor.h"
// #include "market_data_cache.h"

class MarketDataSystem {
private:
    std::vector<std::unique_ptr<ExchangeConnector>> connectors;
    MarketDataProcessor processor;
    // MarketDataDistributor distributor;
    // MarketDataCache cache;
    
    std::thread processing_thread;
    std::thread distribution_thread;
    std::atomic<bool> running{true};
    
public:
    void start();
    void stop();

    void addConnector(const std::string& exchange_name, const std::string& exchange_ip, int port);
    
private:
    void processMessages();
    void distributeMessages();

    uint64_t getCurrentMicroseconds();
    void setCpuAffinity(std::thread& thread, int cpu_core);
};

#endif