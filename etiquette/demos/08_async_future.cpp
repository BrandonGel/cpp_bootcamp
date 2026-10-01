// 08_async_future.cpp — std::async + std::future: results and exceptions without manual joins.
// Build: g++ -std=c++20 -O2 -pthread -Wall -Wextra 08_async_future.cpp -o async
#include <future>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

double partial(const std::vector<double>& v, std::size_t lo, std::size_t hi) {
    return std::accumulate(v.begin() + lo, v.begin() + hi, 0.0);
}

double parallel_sum(const std::vector<double>& v, std::size_t tasks) {
    std::vector<std::future<double>> futures;
    std::size_t chunk = v.size() / tasks;
    for (std::size_t t = 0; t < tasks; ++t) {
        std::size_t lo = t * chunk;
        std::size_t hi = (t + 1 == tasks) ? v.size() : lo + chunk;   // last task takes the remainder
        // std::cref: pass the vector by reference; std::async copies arguments otherwise.
        futures.push_back(std::async(std::launch::async, partial, std::cref(v), lo, hi));
    }
    double total = 0.0;
    for (auto& f : futures) total += f.get();   // waits for each task AND collects its result
    return total;
}

int main() {
    std::vector<double> v(1'000'000, 0.5);
    std::cout << "parallel_sum = " << parallel_sum(v, 4) << " (expected 500000)\n";

    // Exceptions thrown inside the task are stored and re-thrown by get().
    auto bad = std::async(std::launch::async, []() -> int { throw std::runtime_error("task failed"); });
    try {
        bad.get();
    } catch (const std::exception& e) {
        std::cout << "caught from future: " << e.what() << "\n";
    }

    // Pitfall: discarding the future. Its destructor blocks until the task finishes,
    // so this line runs SYNCHRONOUSLY — the program waits right here.
    // (The compiler even warns: std::async is [[nodiscard]]. That warning is the lesson.)
    std::async(std::launch::async, [] { std::cout << "temporary future: ran to completion before the next line\n"; });
    std::cout << "...next line\n";

    // Deferred: runs lazily on the calling thread when get()/wait() is called.
    auto lazy = std::async(std::launch::deferred, [] { return 7; });
    std::cout << "deferred result = " << lazy.get() << "\n";
}
