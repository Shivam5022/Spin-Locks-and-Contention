#pragma once
#include <atomic>
#include <memory>
#include "qnode.hpp"
#include "lock.hpp"

class MCSLock: public Lock {
    std::atomic<std::shared_ptr<QNode>> tail;
    thread_local static std::shared_ptr<QNode> myNode;
    public:
        MCSLock();
        void lock();
        void unlock();
        void type();
        ~MCSLock();
};