#include "../header/MCSLock.hpp"
#include <iostream>

MCSLock::MCSLock() {
    tail = nullptr;
}

MCSLock::~MCSLock() {}

void MCSLock::lock() {
    auto pred = tail.exchange(myNode);
    if (pred != nullptr) {
        myNode->locked = true;
        pred->next = myNode;
        while (myNode->locked) {}
    }
}

void MCSLock::unlock() {
    
    if (myNode->next == nullptr) {
        auto f = myNode;
        if (tail.compare_exchange_strong(myNode, nullptr, std::memory_order_acq_rel)) {
            return;
        }
        myNode = f;
        while (myNode->next == nullptr) {}
    }
    myNode->next->locked = false;
    myNode->next = nullptr;
}

void MCSLock::type() {
    std::cout << "\e[1;33m \u26BF \e[0m";
    std::cout << "MCS Lock used\n";
}

thread_local std::shared_ptr<QNode> MCSLock::myNode(new QNode());