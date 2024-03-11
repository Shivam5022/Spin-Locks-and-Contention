#pragma once
#include <atomic>
#include "lock.hpp"

class TTASLock: public Lock {
    std::atomic<bool> state;
    public:
        TTASLock();
        void lock() ;
        void unlock() ;
        void type() ;
};