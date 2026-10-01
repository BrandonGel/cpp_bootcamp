// 07_threads_mutex_atomic.cpp — a data race, then two fixes (mutex, atomic), plus jthread.
// Build: g++ -std=c++20 -O2 -pthread -Wall -Wextra 07_threads_mutex_atomic.cpp -o threads
// (The racy counter is undefined behavior on purpose — it is here to be observed, never copied.)
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

constexpr int kThreads   = 4;
constexpr int kPerThread = 200'000;

// Launch kThreads copies of fn and join them all; returns elapsed ms.
template <class F>
double run(F fn) {
    auto t0 = std::chrono::steady_clock::now();
    std::vector<std::thread> pool;
    for (int t = 0; t < kThreads; ++t) pool.emplace_back(fn);   // thread starts running NOW
    for (auto& t : pool) t.join();                              // must join (or detach) every one
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
}

void greet(int id, const std::string& msg) {
    static std::mutex io;                     // keep output lines from interleaving
    std::lock_guard<std::mutex> lock(io);
    std::cout << "  thread " << id << ": " << msg << "\n";
}

int main() {
    std::cout << "Passing arguments (copied into the thread):\n";
    {
        std::vector<std::thread> pool;
        for (int i = 0; i < 3; ++i) pool.emplace_back(greet, i, "hello");
        for (auto& t : pool) t.join();
    }

    std::cout << "\nstd::ref to let a thread modify a caller variable:\n";
    int result = 0;
    std::thread writer([](int& out) { out = 42; }, std::ref(result));
    writer.join();
    std::cout << "  result = " << result << "\n";

    const long expected = static_cast<long>(kThreads) * kPerThread;
    std::cout << "\nexpected count: " << expected << "\n";

    // --- Broken: ++racy is read-modify-write; two threads can read the same old value. ---
    volatile long racy = 0;  // volatile only stops the optimizer from hiding the race; it is NOT a fix
    double ms = run([&] { for (int i = 0; i < kPerThread; ++i) racy = racy + 1; });
    std::cout << "  data race : " << racy << "  (" << ms << " ms)  <- lost updates\n";

    // --- Fix 1: a mutex makes the increment a critical section. ---
    long guarded = 0;
    std::mutex m;
    ms = run([&] {
        for (int i = 0; i < kPerThread; ++i) {
            std::lock_guard<std::mutex> lock(m);   // locks here, unlocks at } (RAII)
            ++guarded;
        }
    });
    std::cout << "  mutex     : " << guarded << "  (" << ms << " ms)\n";

    // --- Fix 2: an atomic read-modify-write; no lock object. ---
    std::atomic<long> atomic_counter{0};
    ms = run([&] { for (int i = 0; i < kPerThread; ++i) ++atomic_counter; });
    std::cout << "  atomic    : " << atomic_counter << "  (" << ms << " ms)\n";

    // --- Best: don't share at all. Count locally, combine once. ---
    std::atomic<long> combined{0};
    ms = run([&] {
        long local = 0;
        for (int i = 0; i < kPerThread; ++i) ++local;
        combined += local;                         // one shared write per thread
    });
    std::cout << "  local+sum : " << combined << "  (" << ms << " ms)\n";

    // --- C++20 std::jthread joins automatically in its destructor (RAII). ---
    {
        std::jthread jt([] { greet(99, "jthread joins itself"); });
    }   // joined here
}
