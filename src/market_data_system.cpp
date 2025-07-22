#include "market_data_system.h"

void MarketDataSystem::start() {
    processing_thread = std::thread(&MarketDataSystem::processMessages, this);
    distribution_thread = std::thread(&MarketDataSystem::distributeMessages, this);

    setCpuAffinity(processing_thread, 2);
    setCpuAffinity(distribution_thread, 3);
}

void MarketDataSystem::stop() {
    running.store(false);

    for(auto const& conns : connectors) {
        conns->stop();
    }

    if (processing_thread.joinable()) {
        processing_thread.join();
    }
    if (distribution_thread.joinable()) {
        distribution_thread.join();
    }
}

void MarketDataSystem::addConnector(const std::string& exchange_name, const std::string& exchange_ip, int port) {
    connectors.emplace_back(std::make_unique<ExchangeConnector>(exchange_name, exchange_ip, port));
}

void MarketDataSystem::processMessages() {
    while(running.load()) {
        std::cout << "Process\n";
    }
    
    // MarketDataMessage msg;
    // std::vector<MarketDataMessage> batch;
    
    // while (running.load()) {
    //     // Batch processing for better performance
    //     batch.clear();
        
    //     // Collect multiple messages
    //     while (batch.size() < 100 && processor.getProcessedMessage(msg)) {
    //         batch.push_back(msg);
    //     }
        
    //     if (!batch.empty()) {
    //         cache.batchUpdate(batch);           // Batch update cache
    //         distributor.batchDistribute(batch); // Batch distribute
    //     }
    // }
}

void MarketDataSystem::distributeMessages() {
    while(running.load()) {
        std::cout << "Distribute\n";
    }
}

void MarketDataSystem::setCpuAffinity(std::thread& thread, int cpu_core) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu_core, &cpuset);
    pthread_setaffinity_np(thread.native_handle(), sizeof(cpuset), &cpuset);
}