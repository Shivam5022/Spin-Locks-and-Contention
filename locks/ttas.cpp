#include "../header/ttas.hpp"
#include <iostream>

TTASLock::TTASLock() {
    state.store(false);
}

void TTASLock::lock() {
    while (state.load()) {}
    while (state.exchange(true)) {}
}

void TTASLock::unlock() {
    state.store(false);
}

void TTASLock::type() {
    std::cout << "\e[1;33m \u26BF \e[0m";
    std::cout << "TTAS Lock used\n";
}
