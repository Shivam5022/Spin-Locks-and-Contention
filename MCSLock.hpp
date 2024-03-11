#pragma once
#include <atomic>
#include "qnode.hpp"
#include "lock.hpp"

class MCSLock: public Lock {
    std::atomic<QNode*> tail;
    thread_local static QNode* myNode;
    public:
        MCSLock();
        void lock();
        void unlock();
        void type();
        ~MCSLock();
};