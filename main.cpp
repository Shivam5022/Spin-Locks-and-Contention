#include <chrono>
#include <cassert>
#include <iostream>
#include <random>
#include <thread>

#include "tas.hpp"
#include "ttas.hpp"
#include "alock.hpp"
#include "CLHLock.hpp"
#include "MCSLock.hpp"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) std::uniform_int_distribution<int>(a, b)(rng)

int main() {
    int val = 0;
    int tot = uid(100, 200);

    TASLock f;
    // TTASLock f;
    // ALock f(tot);  //wrong
    // CLHLock f; //wrong
    // MCSLock f;

    std::cout << std::endl;
    f.type();
    std::cout << std::endl;

    auto work = [&]() {
        auto sleep = 30;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
        f.lock();
            val++; val--;
            val *= 2; val /= 2;
            int temp = val; val = 0; val = temp;
            val *= 2; val /= 2;
            val++; val--;
            val++;
        f.unlock();
    };

    std::vector<std::thread> threads;
    for (int j = 0; j < tot; j++) {
        threads.emplace_back(work);
    }

    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    std::cout << val << '\n';
    std::cout << (val == tot ? "YES" : "NO" ) << '\n';

    return 0;
}