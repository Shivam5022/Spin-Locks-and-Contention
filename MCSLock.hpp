#pragma once
#include <atomic>
#include "qnode.hpp"

class MCSLock {
    std::atomic<QNode*> tail;
    thread_local static QNode* myNode;
    public:
        MCSLock();
        void lock();
        void unlock();
        void type();
};