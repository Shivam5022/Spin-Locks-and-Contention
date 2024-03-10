#pragma once
#include <atomic>
#include <vector>

class ALock {
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