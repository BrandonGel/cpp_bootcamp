// Vector2D.h — the DECLARATION: what the class looks like and what it promises.
// Every .cpp that uses Vector2D #includes this file.
#pragma once          // include guard (see etiquette.md §1.1)

#include <iosfwd>     // forward-declares std::ostream; cheaper than <iostream> in a header

class Vector2D {
public:
    Vector2D() = default;                    // (0, 0) thanks to the default member initializers
    Vector2D(double x, double y);            // defined in Vector2D.cpp

    double magnitude() const;                // const: does not modify *this
    double x() const { return x_; }          // tiny accessors may live in the header (implicitly inline)
    double y() const { return y_; }
    void   set_x(double x) { x_ = x; }       // setter: the class stays in control of its data

    Vector2D  operator+(const Vector2D& rhs) const;
    Vector2D& operator+=(const Vector2D& rhs);
    bool      operator==(const Vector2D&) const = default;   // C++20: compiler writes ==

private:
    double x_ = 0.0;   // default member initializers: never uninitialized
    double y_ = 0.0;
};

// Free function: streams are on the LEFT of <<, so this cannot be a member.
std::ostream& operator<<(std::ostream& os, const Vector2D& v);
