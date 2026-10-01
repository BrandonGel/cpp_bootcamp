// main.cpp — uses Vector2D through its header only.
// Build (both .cpp files are compiled, then linked):
//   g++ -std=c++20 -Wall -Wextra main.cpp Vector2D.cpp -o vector2d
#include <iostream>
#include <string>

#include "Vector2D.h"

// Why the initializer list matters: const and reference members CANNOT be assigned in the body.
class Account {
public:
    Account(int id, const std::string& owner) : id_(id), owner_(owner) {}
    // Account(int id, const std::string& owner) { id_ = id; ... }   // error: id_ is const
private:
    const int id_;
    std::string owner_;
};

int main() {
    const Vector2D a(3.0, 4.0);
    Vector2D b(1.0, 2.0);

    std::cout << "a = " << a << ", |a| = " << a.magnitude() << "\n";  // OK: magnitude() is const
    std::cout << "a + b = " << a + b << "\n";

    b += a;
    std::cout << "b after += a: " << b << "\n";
    std::cout << "b == (4,6)? " << std::boolalpha << (b == Vector2D(4.0, 6.0)) << "\n";

    // a.set_x(1.0);   // error: a is const and set_x() is not a const member function
    // a.x_ = 5.0;     // error: x_ is private

    Account acc(42, "Brandon");
    (void)acc;
}
