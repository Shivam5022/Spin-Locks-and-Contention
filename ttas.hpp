#pragma once
#include <atomic>

class TTASLock {
    std::atomic<bool> state;
    public:
        TTASLock();
        void lock();
        void unlock();
        void type();
};