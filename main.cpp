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
    int tot = uid(20, 80);

    std::vector<Lock*> locks(5);
    locks[0] = new TASLock;
    locks[1] = new TTASLock;
    locks[2] = new ALock(tot);
    locks[3] = new CLHLock;
    locks[4] = new MCSLock;

    auto criticalSection = [&](Lock* f) {
        f->lock();
            for (int i = 0; i < 300; i++) {
                val++; val--;
                val *= 2; val /= 2;
                int temp = val; val = 0; val = temp;
            }
            val += 2;
        f->unlock();
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