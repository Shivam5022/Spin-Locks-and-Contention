#pragma once
#include <atomic>

class TASLock {
    std::atomic<bool> state;
    public:
        TASLock();
        void lock();
        void unlock();
        void type();
};
