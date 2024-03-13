#include "../header/tas.hpp"
#include <iostream>

TASLock::TASLock() {
    state.store(false);
}

void TASLock::lock() {
    while (state.exchange(true)) {}
}

void TASLock::unlock() {
    state.store(false);
}

void TASLock::type() {
    std::cout << "\e[1;33m \u26BF \e[0m";
    std::cout << "TAS Lock used\n";
}












