#include "exchange_connector.h"

ExchangeConnector::ExchangeConnector(const std::string& exchange_name, const std::string& exchange_ip, int port) 
    : exchange_name(exchange_name), exchange_ip(exchange_ip), port(port) {

    message_queue = std::make_unique<LockFreeQueue<MarketDataMessage, QUEUE_SIZE>>();

    // setupSocket();
    
    worker_thread = std::thread(&ExchangeConnector::receiveData, this);
}

ExchangeConnector::~ExchangeConnector() {
    stop();
}

void ExchangeConnector::stop() {
    running.store(false);

    if (socket_fd >= 0) {
        close(socket_fd);
    }

    if (worker_thread.joinable()) {
        worker_thread.join();
    }
}


void ExchangeConnector::receiveData() { // add batch processing
    char buffer[4096];
    while (running.load()) {
        std::cout << "Receive data\n";
    }
}

void ExchangeConnector::setupSocket() {
    // implement
}