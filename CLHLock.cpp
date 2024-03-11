#include "CLHLock.hpp"
#include <iostream>

CLHLock::CLHLock() {
    tail = new QNode();
}

void CLHLock::lock() {
    myNode->locked = true;
    QNode* pred = tail.exchange(myNode);
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

thread_local QNode* CLHLock::myNode = new QNode(); 
thread_local QNode* CLHLock::myPred = nullptr; 
