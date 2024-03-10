#include "tas.hpp"
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
    std::cout << "TAS Lock used\n";
}



// class BackoffLock {
//     std::atomic<bool> state;
//     public:
//         BackoffLock() {
//             state.store(false);
//         }
//         void lock() {
//             int MAX_DELAY = 100;
//             int MIN_DELAY = 5;
//             int limit = MIN_DELAY;
//             while (true) {
//                 while (state.load()) {}
//                 if (!state.exchange(true)) {
//                     return;
//                 } else {
//                     auto delay = uid(limit, MAX_DELAY);
//                     limit = std::min(MAX_DELAY, 2 * limit);
//                     std::this_thread::sleep_for(std::chrono::milliseconds(delay));
//                 }
//             }
//         }
//         void unlock() {
//             state.store(false);
//         }
// };











