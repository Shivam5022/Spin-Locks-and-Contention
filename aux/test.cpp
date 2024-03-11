#include <cassert>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "atomics.hpp"

int main() {

    int num = 10;
    int original = 100;
    std::vector<int> final(num);
    std::vector<int> got(num);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(50, 10000);

    auto work = [&](int id, int proposed) {
        auto sleep = 100;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
        int chosen = 0;
        chosen = getAndSet(&original, &proposed);
        final[id] = proposed;
        got[id] = chosen;
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < num; i++) {
        int proposed = distrib(gen);
        std::cout << i << ' ' << proposed << '\n';
        threads.emplace_back(work, i, proposed);
    }

    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    for (int i = 0; i < num; i++) {
        std::cout << "Thread " << i << " chose value = " << final[i] << "\n";
        std::cout << "Thread " << i << " got value = " << got[i] << "\n";
        std::cout << std::endl;
    }

    return 0;
}