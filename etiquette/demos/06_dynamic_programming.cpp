// 06_dynamic_programming.cpp — naive recursion vs memoization vs tabulation.
// Build: g++ -std=c++20 -O2 -Wall -Wextra 06_dynamic_programming.cpp -o dp
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

using u64 = std::uint64_t;

u64 fib_naive(int n) { return n < 2 ? n : fib_naive(n - 1) + fib_naive(n - 2); }   // O(2^n)

// Top-down: same recursion, cache each answer the first time it is computed. O(n)
u64 fib_memo(int n, std::vector<u64>& memo) {
    if (n < 2) return n;
    if (memo[n] != 0) return memo[n];
    return memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
}

// Bottom-up: fill the table from the base cases. No recursion. O(n) time, O(n) space
u64 fib_table(int n) {
    if (n < 2) return n;
    std::vector<u64> t(n + 1);
    t[1] = 1;
    for (int i = 2; i <= n; ++i) t[i] = t[i - 1] + t[i - 2];
    return t[n];
}

// Bottom-up, space-optimized: only the last two rows are ever needed. O(1) space
u64 fib_rolling(int n) {
    u64 a = 0, b = 1;
    for (int i = 0; i < n; ++i) { u64 next = a + b; a = b; b = next; }
    return a;
}

template <class F>
void timeit(const char* label, F f) {
    auto t0 = std::chrono::steady_clock::now();
    u64 r = f();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(
                  std::chrono::steady_clock::now() - t0).count();
    std::cout << label << r << "  (" << us << " us)\n";
}

int main() {
    const int n = 35;
    timeit("naive   fib(35) = ", [] { return fib_naive(n); });
    timeit("memo    fib(35) = ", [] { std::vector<u64> memo(n + 1, 0); return fib_memo(n, memo); });
    timeit("table   fib(35) = ", [] { return fib_table(n); });
    timeit("rolling fib(90) = ", [] { return fib_rolling(90); });
}
