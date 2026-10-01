// Vector2D.cpp — the DEFINITIONS (function bodies). Compiled as its own translation unit.
#include "Vector2D.h"

#include <cmath>
#include <ostream>

// Member initializer list: x_ and y_ are constructed directly with these values.
Vector2D::Vector2D(double x, double y) : x_(x), y_(y) {}

double Vector2D::magnitude() const { return std::sqrt(x_ * x_ + y_ * y_); }

Vector2D Vector2D::operator+(const Vector2D& rhs) const {
    return Vector2D(x_ + rhs.x_, y_ + rhs.y_);   // members can read rhs's private data
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;                                // return *this so `a += b += c` works
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    return os << '(' << v.x() << ", " << v.y() << ')';   // uses the public interface only
}
