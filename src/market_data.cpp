#include <iostream>
#include "market_data_system.h"

int main() {
    MarketDataSystem market;

    market.addConnector("NYSE", "224.1.1.1", 9001); 
    market.addConnector("NASDAQ", "224.1.1.2", 9002); 
    
    market.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    market.stop();

    return 0;
}