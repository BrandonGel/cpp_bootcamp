// 02_algorithms_lambdas.cpp — <algorithm>, <numeric>, and lambda captures.
// Build: g++ -std=c++20 -Wall -Wextra 02_algorithms_lambdas.cpp -o algos
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> data{5, 9, 2, 7, 1, 8};

    // std::sort — ascending by default, or pass a comparison.
    std::sort(data.begin(), data.end());
    std::sort(data.begin(), data.end(), [](int a, int b) { return a > b; });  // descending

    // std::find_if — returns an iterator to the FIRST element where the predicate is true.
    auto it = std::find_if(data.begin(), data.end(), [](int v) { return v < 7; });
    if (it != data.end())   // always check against end() before dereferencing
        std::cout << "first value < 7 (descending order): " << *it << "\n";

    // std::accumulate — fold with + (or any binary op). The init value sets the result TYPE.
    int    sum  = std::accumulate(data.begin(), data.end(), 0);
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    std::cout << "sum = " << sum << ", mean = " << mean << "\n";

    // --- Lambda captures ---
    int threshold = 4;
    int hits = 0;

    auto by_value = [threshold](int v) { return v > threshold; };   // copy taken NOW
    auto by_ref   = [&hits](int v) { if (v % 2 == 0) ++hits; };    // modifies the original

    threshold = 100;   // by_value still uses its copy (4)
    std::cout << "count > 4 (captured copy): "
              << std::count_if(data.begin(), data.end(), by_value) << "\n";

    std::for_each(data.begin(), data.end(), by_ref);
    std::cout << "even values counted via [&hits]: " << hits << "\n";

    // A by-value capture is const inside the lambda unless you add `mutable`.
    int calls = 0;
    auto counter = [calls]() mutable { return ++calls; };  // changes the lambda's OWN copy
    counter(); counter();
    std::cout << "counter() returned " << counter() << ", outer calls still " << calls << "\n";

    // Etiquette: prefer listing captures explicitly over [=] / [&] in long-lived lambdas,
    // and never capture locals by reference in a lambda that outlives the scope (dangling!).
}
