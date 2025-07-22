#ifndef MARKET_DATA_UTIL_H
#define MARKET_DATA_UTIL_H

#include <cstddef>
#include <cstdint>
#include <chrono>

static constexpr std::size_t QUEUE_SIZE = 1000000;
static constexpr std::size_t SOCKET_BUFFER_SIZE = 1024 * 1024;

inline uint64_t getCurrentMicroseconds() {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
}

#endif