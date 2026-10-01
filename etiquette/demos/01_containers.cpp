// 01_containers.cpp — how the standard containers behave in memory.
// Build: g++ -std=c++20 -Wall -Wextra 01_containers.cpp -o containers
#include <array>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    // --- std::array: fixed size known at compile time, elements are still mutable ---
    std::array<int, 4> fixed{3, 1, 4, 1};
    fixed[0] = 9;                          // OK: the SIZE is fixed, the VALUES are not
    std::cout << "array size " << fixed.size() << ", first = " << fixed[0] << "\n";

    // --- std::vector: watch size vs capacity. Reallocation only happens when size == capacity ---
    std::vector<int> v;
    std::size_t last_cap = v.capacity();
    std::cout << "\nvector growth (push_back 0..32):\n";
    for (int i = 0; i <= 32; ++i) {
        v.push_back(i);
        if (v.capacity() != last_cap) {
            std::cout << "  size " << v.size() << " -> capacity grew " << last_cap
                      << " -> " << v.capacity() << " (reallocate + move elements)\n";
            last_cap = v.capacity();
        }
    }

    // reserve() up front avoids every reallocation above.
    std::vector<int> r;
    r.reserve(33);
    for (int i = 0; i <= 32; ++i) r.push_back(i);
    std::cout << "with reserve(33): capacity stayed " << r.capacity() << "\n";

    // --- std::list: no operator[]; you walk node by node ---
    std::list<int> lst{10, 20, 30};
    auto it = lst.begin();
    std::advance(it, 1);                  // O(n) walk, not O(1) indexing
    lst.insert(it, 15);                   // O(1) insert once you are there
    std::cout << "\nlist: ";
    for (int x : lst) std::cout << x << ' ';
    std::cout << "\n";

    // --- std::map (ordered, O(log n)) vs std::unordered_map (hash, O(1) average) ---
    std::map<std::string, int> ordered{{"pear", 3}, {"apple", 5}, {"fig", 1}};
    std::unordered_map<std::string, int> hashed{{"pear", 3}, {"apple", 5}, {"fig", 1}};
    std::cout << "\nmap iterates in key order:      ";
    for (const auto& [k, val] : ordered) std::cout << k << '=' << val << ' ';
    std::cout << "\nunordered_map has no set order: ";
    for (const auto& [k, val] : hashed) std::cout << k << '=' << val << ' ';
    std::cout << "\n";

    // Etiquette: operator[] INSERTS a default value when the key is missing.
    std::cout << "\nordered.size() before ordered[\"kiwi\"]: " << ordered.size();
    int kiwi = ordered["kiwi"];           // silently inserts {"kiwi", 0}
    std::cout << ", after: " << ordered.size() << " (kiwi=" << kiwi << ")\n";
    // Look up without inserting:
    if (auto found = ordered.find("grape"); found == ordered.end())
        std::cout << "find(\"grape\") -> not found, nothing inserted\n";
    std::cout << "contains(\"fig\") -> " << std::boolalpha << ordered.contains("fig") << "\n";  // C++20
}
