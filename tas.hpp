#pragma once
#include <atomic>
#include "lock.hpp"

class TASLock: public Lock {
    std::atomic<bool> state;
    public:
        TASLock();
        void lock();
        void unlock();
        void type();
};
