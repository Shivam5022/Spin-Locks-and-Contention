#pragma once
#include <atomic>
#include <vector>
#include "qnode.hpp"
#include "lock.hpp"

class CLHLock :public Lock {
    std::atomic<QNode*> tail;
    thread_local static QNode* myNode;
    thread_local static QNode* myPred;
    public:
        CLHLock();
        void lock() ;
        void unlock() ;
        void type() ;
};