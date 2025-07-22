#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <array>
#include <atomic>
#include <cstddef>

template<typename T, size_t SIZE>
class LockFreeQueue {
private:
    std::array<T, SIZE> buffer;
    std::atomic<size_t> head{0};
    std::atomic<size_t> tail{0};
    
public:
    bool push(const T& item) {
        size_t current_tail = tail.load();
        size_t next_tail = (current_tail + 1) % SIZE;
        
        if (next_tail == head.load()) {
            return false;
        }
        
        buffer[current_tail] = item;
        tail.store(next_tail);
        return true;
    }
    
    bool pop(T& item) {
        size_t current_head = head.load();
        if (current_head == tail.load()) {
            return false;
        }
        
        item = buffer[current_head];
        head.store((current_head + 1) % SIZE);
        return true;
    }

    bool empty() const {
        return head.load(std::memory_order_relaxed) == tail.load(std::memory_order_relaxed);
    }
    
    size_t size() const {
        size_t h = head.load(std::memory_order_relaxed);
        size_t t = tail.load(std::memory_order_relaxed);
        return (t >= h) ? (t - h) : (SIZE - h + t);
    }
};

#endif

// try aligned_alloc later...