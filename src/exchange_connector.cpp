#include "exchange_connector.h"

ExchangeConnector::ExchangeConnector(const std::string& exchange_name, const std::string& exchange_ip, int port) 
    : exchange_name(exchange_name), exchange_ip(exchange_ip), port(port) {

    setupSocket();
    
    worker_thread = std::thread(&ExchangeConnector::receiveData, this);
}

void ExchangeConnector::stop() {
    running.store(false);
}

ExchangeConnector::~ExchangeConnector() {
    stop();
    if (worker_thread.joinable()) {
        worker_thread.join();
    }
    if (socket_fd >= 0) {
        close(socket_fd);
    }
}

void ExchangeConnector::receiveData() {
    std::cout << "Receive data\n";
    // char buffer[1024];
    // while (true) {
    //     ssize_t bytes = recv(socket_fd, buffer, sizeof(buffer), 0);
    //     if (bytes > 0) {
    //         auto msg = MarketDataMessage::deserialize(buffer);
    //         // msg.timestamp = getCurrentMicroseconds();
    //         message_queue.push(msg);
    //     }
    // }
}

void ExchangeConnector::setupSocket() {
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        throw std::runtime_error("Failed to create socket for " + exchange_name);
    }
    
    int opt = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, exchange_ip.c_str(), &addr.sin_addr);
    
    bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr));
}