#include <chrono>
#include <cassert>
#include <iostream>
#include <random>
#include <thread>

#include "header/tas.hpp"
#include "header/ttas.hpp"
#include "header/alock.hpp"
#include "header/CLHLock.hpp"
#include "header/MCSLock.hpp"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) std::uniform_int_distribution<int>(a, b)(rng)

int main() {
    int val = 0;
    int tot = 10;

    std::vector<Lock*> locks(5);
    locks[0] = new TASLock;
    locks[1] = new TTASLock;
    locks[2] = new ALock(tot);
    locks[3] = new CLHLock;
    locks[4] = new MCSLock;

    // std::vector<Lock*> locks(5, new MCSLock);

    auto criticalSection = [&](Lock* f) {
        // auto start = std::chrono::high_resolution_clock::now();
        f->lock();
            for (int i = 0; i < 500; i++) {
                val++; val--;
                val *= 2; val /= 2;
                int temp = val; val = 0; val = temp;
            }
            val += 2;
        f->unlock();
        // auto end = std::chrono::high_resolution_clock::now();
    };

    for (auto& f: locks) {
        f->type();

        std::vector<std::thread> threads;
        for (int j = 0; j < tot; j++) {
            threads.emplace_back(criticalSection, f);
        }

        for (auto &thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        std::cout << val << ' ' << tot*2 << '\n';
        std::cout << (val == tot*2 ? "YES" : "NO" ) << "\n\n";
        val = 0;
    }

    return 0;
}