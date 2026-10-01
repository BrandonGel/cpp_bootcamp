// 04_raii_smart_pointers.cpp — RAII, the Rule of 0/3/5, and smart pointers.
// Build: g++ -std=c++20 -Wall -Wextra 04_raii_smart_pointers.cpp -o raii
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

// A class that MANUALLY owns a resource (a heap buffer) => it needs the Rule of Five.
class Buffer {
public:
    explicit Buffer(std::size_t n) : size_(n), data_(new int[n]{}) {
        std::cout << "  acquire " << n << " ints\n";
    }
    ~Buffer() {                                    // 1. destructor
        if (data_) std::cout << "  release " << size_ << " ints\n";
        delete[] data_;
    }
    Buffer(const Buffer& other)                    // 2. copy constructor: deep copy
        : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "  deep copy " << size_ << " ints\n";
    }
    Buffer& operator=(Buffer other) noexcept {     // 3. copy assignment (copy-and-swap)
        swap(other);                               //    also serves as 5. move assignment
        return *this;
    }
    Buffer(Buffer&& other) noexcept                // 4. move constructor: steal, leave other empty
        : size_(std::exchange(other.size_, 0)), data_(std::exchange(other.data_, nullptr)) {}

    void swap(Buffer& o) noexcept { std::swap(size_, o.size_); std::swap(data_, o.data_); }
    std::size_t size() const { return size_; }

private:
    std::size_t size_;
    int* data_;
};

// Rule of ZERO: build classes out of members that already manage themselves.
// No destructor, no copy/move functions — the compiler-generated ones are correct.
class Image {
public:
    Image(int w, int h) : pixels_(static_cast<std::size_t>(w) * h) {}
private:
    std::vector<unsigned char> pixels_;   // vector does the RAII for us
};

void may_throw(bool fail) {
    Buffer local(3);                      // acquired here...
    if (fail) throw std::runtime_error("boom");
    std::cout << "  normal return\n";
}                                         // ...released here, on BOTH paths

int main() {
    std::cout << "RAII on normal exit:\n";
    may_throw(false);

    std::cout << "RAII during an exception:\n";
    try { may_throw(true); } catch (const std::exception& e) { std::cout << "  caught: " << e.what() << "\n"; }

    std::cout << "Copy vs move:\n";
    Buffer a(4);
    Buffer b = a;                // copy: deep copy printed
    Buffer c = std::move(a);     // move: no allocation, a is now empty
    std::cout << "  a.size()=" << a.size() << " c.size()=" << c.size() << "\n";
    (void)b;

    std::cout << "unique_ptr (sole owner, move-only):\n";
    {
        auto p = std::make_unique<Buffer>(2);       // no naked `new`
        // auto q = p;                              // error: unique_ptr cannot be copied
        auto q = std::move(p);                      // ownership transferred
        std::cout << "  p is " << (p ? "set" : "null") << ", q owns it\n";
    }                                               // q destroyed -> Buffer released

    std::cout << "shared_ptr (reference counted):\n";
    {
        auto s1 = std::make_shared<Buffer>(1);
        {
            auto s2 = s1;
            std::cout << "  use_count = " << s1.use_count() << "\n";
        }
        std::cout << "  use_count = " << s1.use_count() << "\n";
    }                                               // last owner gone -> released

    Image img(4, 4);  (void)img;
    std::cout << "end of main (remaining Buffers released below)\n";
}
