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

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
#define uid(a, b) std::uniform_int_distribution<int>(a, b)(rng)

int main(int argc, char** argv) {
    int val = 0;
    int tot = std::stoi(argv[1]);

    std::vector<Lock*> locks(5);
    locks[0] = new TASLock;
    locks[1] = new TTASLock;
    locks[2] = new ALock(tot);
    locks[3] = new CLHLock;
    locks[4] = new MCSLock;

    std::cerr << std::endl;
    std::cerr << "Total Threads: " << tot << std::endl;
    std::cerr << std::endl;

    auto criticalSection = [&](Lock* f, int limit) {
        f->lock();
            for (int i = 1; i <= limit; i += 1) {
                val += 1;
            }
        f->unlock();
    };

    for (auto& f: locks) {
        auto start = std::chrono::high_resolution_clock::now();
        f->type();

        std::vector<std::thread> threads;
        for (int j = 0; j < tot; j++) {
            threads.emplace_back(criticalSection, f, 1'000'000 / tot);
        }

        for (auto &thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << duration.count() / tot << std::endl; // avg time per thread

        auto z = 1'000'000;
        if (val == z) std::cerr << GREEN << "CORRECT" << RESET << "\n\n";
        else std::cerr << RED << "INCORRECT" << RESET << "\n\n";
        val = 0;
    }

    for (int i = 0; i < 5; i++) {
        delete locks[i];
    }

    return 0;
}