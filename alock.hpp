#pragma once
#include <atomic>
#include <vector>
#include "lock.hpp"

class ALock: public Lock {
    thread_local static int mySlotIndex;
    int size;
    std::atomic<int> tail;
    std::vector<bool> flag;

    public:
        ALock (int capacity);
        void lock();
        void unlock();
        void type();
};