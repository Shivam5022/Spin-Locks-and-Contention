#include "MCSLock.hpp"
#include <iostream>

MCSLock::MCSLock() {
    tail = nullptr;
    myNode = new QNode;
}

void MCSLock::lock() {
    QNode* pred = tail.exchange(myNode);
    if (pred != nullptr) {
        myNode->locked = true;
        pred->next = myNode;
        while (myNode->locked) {}
    }
}

void MCSLock::unlock() {
    if (myNode->next == nullptr) {
        if (tail.compare_exchange_strong(myNode, nullptr)) {
            return;
        }
        while (myNode->next == nullptr) {}
    }
    myNode->next->locked = false;
    myNode->next = nullptr;
}

void MCSLock::type() {
    std::cout << "MCS Lock used\n";
}

thread_local QNode* MCSLock::myNode = new QNode;