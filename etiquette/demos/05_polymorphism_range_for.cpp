// 05_polymorphism_range_for.cpp — virtual/override, abstract bases, and range-based for.
// Build: g++ -std=c++20 -Wall -Wextra 05_polymorphism_range_for.cpp -o shapes
#include <iostream>
#include <memory>
#include <numbers>
#include <string>
#include <vector>

class Shape {                                     // abstract: has pure virtual functions
public:
    virtual ~Shape() = default;                   // virtual dtor: delete via Shape* is safe
    virtual double area() const = 0;              // pure virtual: no body, MUST be overridden
    virtual std::string name() const { return "Shape"; }   // virtual with a default body
};

class Circle : public Shape {
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return std::numbers::pi * r_ * r_; }
    std::string name() const override { return "Circle"; }
private:
    double r_;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    std::string name() const override { return "Rectangle"; }
    // double area() override { ... }   // error thanks to `override`: missing const => no match
private:
    double w_, h_;
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));

    double total = 0.0;
    for (const auto& s : shapes) {               // const auto&: read-only, no copy
        // The function that runs is chosen at RUN time from the object's real type.
        std::cout << s->name() << " area = " << s->area() << "\n";
        total += s->area();
    }
    std::cout << "total = " << total << "\n";
    // for (auto s : shapes) {}                  // error: would COPY a unique_ptr

    // --- The three range-for forms ---
    std::vector<int> nums{1, 2, 3};
    for (auto n : nums) n *= 10;                 // copy: changes are thrown away
    std::cout << "after `auto`:        " << nums[0] << nums[1] << nums[2] << "\n";
    for (auto& n : nums) n *= 10;                // reference: modifies the elements
    std::cout << "after `auto&`:       " << nums[0] << ' ' << nums[1] << ' ' << nums[2] << "\n";
    int sum = 0;
    for (const auto& n : nums) sum += n;         // const reference: read, no copy, can't modify
    std::cout << "sum via const auto&: " << sum << "\n";
}
