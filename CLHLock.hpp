#pragma once
#include <atomic>
#include <vector>
#include <memory>
#include "qnode.hpp"
#include "lock.hpp"

class CLHLock :public Lock {
    std::atomic<std::shared_ptr<QNode>> tail;
    thread_local static std::shared_ptr<QNode> myPred;
    thread_local static std::shared_ptr<QNode> myNode;
    public:
        CLHLock();
        ~CLHLock();
        void lock() ;
        void unlock() ;
        void type() ;
};