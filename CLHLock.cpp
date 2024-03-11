#include "CLHLock.hpp"
#include <iostream>

CLHLock::CLHLock() {
    tail = std::shared_ptr<QNode>(new QNode());
}

CLHLock::~CLHLock() {}

void CLHLock::lock() {
    myNode->locked = true;
    std::shared_ptr<QNode> pred = tail.exchange(myNode);
    myPred = pred;
    while (pred->locked) {}
}

void CLHLock::unlock() {
    myNode->locked = false;
    myNode = myPred;
}

void CLHLock::type() {
    std::cout << "CLH Lock used\n";
}

thread_local std::shared_ptr<QNode> CLHLock::myPred(nullptr);
thread_local std::shared_ptr<QNode> CLHLock::myNode(new QNode());
