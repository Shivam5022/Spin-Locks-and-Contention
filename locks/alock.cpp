#include "../header/alock.hpp"
#include <iostream>

ALock::ALock (int capacity) {
    size = capacity;
    tail.store(0);
    flag.assign(size, false);
    flag[0] = true;
}

void ALock::lock() {
    int slot = (tail.fetch_add(1)) % size;
    mySlotIndex = slot;
    while (!flag[slot]) {};
}

void ALock::unlock() {
    int slot = mySlotIndex;
    flag[slot] = false;
    flag[(slot + 1) % size] = true;
}

void ALock::type() {
    std::cout << "Anderson Lock used\n";
}

thread_local int ALock::mySlotIndex = 0;
