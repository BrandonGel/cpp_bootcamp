
# Vector, Array, List, Map
- **`<T> []`** - a fixed size array that assigns memory at the start 
  - Immutable but quick to fsearch/index
- **`std::vector<T>`** — a growable array that owns and manages its own memory. 
  - Mutable but adding a new element -> create a new variable, allocate a larger memory to the new variable, and copy the content of the old vector to the new vector
- **`std::list<T>`** - doubly link list that is growable
  - Randomly select points is not possible -> need to iterate the list from either the start or the end
- **`std::map<T>`** - lookup table with a key and a value
  - Get the best of a list and an array
- **`std::string`** — a growable, owning text string; no manual buffers, no `strcpy`.

# Useful functions/algorithms
## **`#include <algorithm>`**  
  - **`#std::sort`** - sort the data structure
    -   std::sort(data.begin(), data.end());
  - **`#std::find_if`** - use a lambda expression to the first item in a data structure
    - auto it = std::find_if(data.begin(), data.end(),[](int v) { return v >= 7; });
##  **`#include <numeric>`**     
  - **`#std::accumulate`** - sum up all the values
    - int sum  = std::accumulate(data.begin(), data.end(), 0);
## lambda function
  - [] {} syntax
    - [] - Captures nothing. Only has access to arguments passed directly to it
    - [x] - Captures variable x by value (read-only copy)
    - [&x] - Captures variable x by reference (can modify the original variable)
    - [=] - Default capture: captures all used local variables by value
    - [&] - Default capture: captures all used local variables by reference
    - [=, &x] - Captures everything by value, but x by reference.
    - {} - Define the lambda function scope
##  **`#include <atomic>`**     
  - **`#std::atomic<T>`** - create a template class of type T
    - Provide protection to maintain a consistent count for multi-threading (remove overlapping)
    - Limit access to only one thread have access over a variable at any given time (slow down program a bit)


# Class & Struct
## Definition
A **class** is a user-defined type that groups together some *data* (member variables) and the
*functions* that act on that data (member functions, also called methods), and then draws a line
between what is visible to the outside world and what is hidden inside.

That line is drawn with **access specifiers**:

- **`public`** members form the class's *interface* — the operations any code may call.
- **`protected`** members form the class's *internal interface* — the operations derived classes may call.
- **`private`** members are the *implementation* — reachable only by the class's own functions.

Keeping the data private and exposing a small public interface is **encapsulation**. It means the
class alone is responsible for keeping its data consistent (its *invariants*), and you are free to
change how it works internally without breaking any code that uses it. Everyone else programs against
the interface, not the internals.

> A `struct` and a `class` in C++ are the *same* mechanism with one difference: members of a `struct`
> are `public` by default, members of a `class` are `private` by default. By convention we use
> `struct` for plain bundles of data and `class` when there is behavior and invariants to protect.

## Class Etiquette
- Initializer list - initalize the variable once (performance boost)
  - Constructor initalizes the variables first, so no need to initalize inside the scope of the constructor
- 'const' after the parameter list (read only)
  - Let the complier and the users to know that the function does not change any of the class parameters
- getter - get a parameter from the class without changing the parameter value
- setter - set/change the value of the parameter
- overload - change how operations/methods to behave

class Vector2D 
{
public:
    // Constructor: runs when a Vector2D is created. The ": x_(x), y_(y)" part is a
    // MEMBER INITIALIZER LIST — it initializes the members directly.
    Vector2D(double x, double y) : x_(x), y_(y) {}

    // "const" after the parameter list promises this function won't modify the object.
    double magnitude() const { return std::sqrt(x_ * x_ + y_ * y_); }
    double x() const { return x_; }          // public accessors expose read-only views
    double y() const { return y_; }

    // Operator overloading: define what "a + b" means for two Vector2D values.
    // It may read rhs.x_ / rhs.y_ directly because operator+ is a member of the class.
    Vector2D operator+(const Vector2D& rhs) const 
    {
        return Vector2D(x_ + rhs.x_, y_ + rhs.y_);
    }

private:
    double x_;   // private: only Vector2D's own functions may touch these
    double y_;
};

- **The constructor** `Vector2D(double x, double y)` runs whenever a `Vector2D` is created, and its
  job is to leave the object in a valid state. The `: x_(x), y_(y)` after the signature is a **member
  initializer list**, which initializes each member *directly* — prefer it to assigning inside the
  body (more on why in the practice problems).
- **`const` member functions** — `magnitude()`, `x()`, `y()` are all marked `const`, promising not to
  change the object. You can call them on a `const Vector2D`, and the compiler enforces the promise.
  Const-correctness is not busywork: later it is what makes an object safe to share across threads.
- **Encapsulation** — `x_` and `y_` are `private`. Code outside the class reaches them only through
  the public accessors, so `Vector2D` stays in control of its own data. Uncomment the `a.x_ = 5.0;`
  line to watch the compiler reject it.
- **Operator overloading** — `operator+` gives `+` a meaning for your type; the free function
  `operator<<` teaches streams how to print it. Overload operators only when the meaning is obvious
  (adding vectors is; "multiplying" two employees is not).

# RAII (Resource Allocation is Initalization
> **Tie a resource's lifetime to an object's lifetime.** Acquire the resource in the constructor;
> release it in the destructor. Then the resource is cleaned up *automatically* and *deterministically*
> the moment the object goes out of scope.

A **destructor** (`~ClassName()`) is the mirror of the constructor: the compiler calls it
automatically when an object is destroyed — when a local variable reaches the closing `}` of its
scope, or an owning container is destroyed. You never call it by hand, and — crucially — it runs even
if the scope is left early by an exception.

Rule of Three's: When working with custom RAII, create a copy constructor, a copy assignment, and a destructor
https://www.geeksforgeeks.org/cpp/rule-of-three-in-cpp/

Rule of Five's: When working with custom RAII, create a copy constructor, a copy assignment, a move constructor, a move assignment, and a destructor
https://www.geeksforgeeks.org/cpp/rule-of-five-in-cpp/

# Inheritance and Polymorphism
- virtual - set the base function to be empty and be filled out in the inherited class
- override - tell the inherited class to fill in the virtual function and NOT create a new function with the same name (save memory)

  // Abstract base class: it declares an interface but defines no objects of its own.
class Shape {
public:
    virtual ~Shape() = default;               // virtual destructor: required for a polymorphic base
    virtual double area() const = 0;          // "= 0" => pure virtual => Shape is abstract
    virtual std::string name() const = 0;
};

class Circle : public Shape {                 // "Circle is a Shape"
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.141592653589793 * r_ * r_; }
    std::string name() const override { return "Circle"; }
private:
    double r_;
};

# Smart Pointer
- **`std::unique_ptr`** - maintain the lifetime of a pointer
  - When the pointer goes out of scope, memory is free
- **`std::make_unique`** - create a unique pointer of a data type
  - Skip in creating **`new`** for creating a pointer (save time in writing)

# Range based forloop 
- Iterate through the items in the forloop without making a copy, keeping the changes being made, and not changing the data
- Without const and &, we create a copy and lose the changes we made
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Circle>(2.0));
  shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));
  for (const auto& s : shapes) {
      // Which area()/name() runs is decided at run time from the object's REAL type.
      std::cout << s->name() << " area = " << s->area() << "\n";
      total += s->area();
  }

# C++ organization (header & cpp files)
- the **header** (`.h`) holds the **declaration** — the class definition and the *signatures* of its
  functions. Anyone who uses the class `#include`s this.
  - Add **`# pragma once`** : a type of guard (new school) & may not work on old compliers
  - **`#ifndef`**, **`#define`**, **`#endif`** : a type of guard (old school) & always work 
- the **source** (`.cpp`) holds the **definitions** — the function bodies, written as
  `ClassName::function`. It is compiled **once**.

# Dynamic Programming
- Top-down memoization: same recursion, but cache each answer the first time it is found.
  - Compute subproblems that are reachable from the current state
  - Great when the state space is large, but the states themselves are rarely visited
  - Required recursion
- Bottom-up tabulation: fill a table from the base cases upward. No recursion.
  -  No recursion needed and no memory function overhead
  -  Shrink the memory of the table by keeping only part of the table you need
 
# CMake
- Create two types of cmakelist.txt (1 for top-level for standardizing all low-level cmake to follow and 1 for low-level for cpp)
- Create a build directory in your project and **`cd build`** 
- Then run **`cmake ../.`** to create the make files in the build directory
- Then run **`cmake --build . -j`** to create the executables

# Threads
## **`#include <thread>`** 
- **`std::thread`** - creates a thread class of a function
- **`T.join()`**  - have the cpp pauses until the thread is finished
- thread creation is slow (takes ms)
- When a thread is done, it goes into an idle state
## Etiquette
- **`pool.emplace_back(greet, i, "…")`** constructs a `std::thread` in place that will call
  `greet(i, "…")`. The `i` is copied; had `greet` needed to *modify* a caller variable, you would pass
  `std::ref(var)`.
- **`t.join()`** waits for thread `t` to finish. We join every thread in the pool before `main`
  returns.
- **The must-join rule** is RAII wearing a stricter face: forget to join (or detach) and the
  `std::thread` destructor calls `std::terminate()`. The cleanest habit is to always join, often from a
  wrapper whose destructor joins for you; **C++20**'s `std::jthread` does exactly that automatically,
  but this course targets C++17, so we join by hand.
## Hazard: data races
- Threads become dangerous the moment two of them touch the **same** data and at least one is writing.
- Safeguard
  - A **`std::mutex`** (mutual exclusion) protects a **critical section** — a region only one thread may execute at a time. You do not lock and unlock it by hand; you use a **`std::lock_guard`**, whose constructor locks and whose destructor unlocks. That is RAII from Lecture 2 again: the lock is released automatically when the guard leaves scope, even if an exception is thrown.
  - A **`std::atomic<T>`** makes operations on a single variable **indivisible** at the hardware level, with no lock at all. For a lone counter, `++atomicCounter` is one uninterruptible read-modify-write — exactly what the race was missing.

    // --- Fix 1: a mutex makes the increment a critical section (one thread at a time). ---
    long guarded = 0;
    std::mutex m;
    auto work_mutex = [&] {
        for (int i = 0; i < kPerThread; ++i) {
            std::lock_guard<std::mutex> lock(m);   // locks here; unlocks at end of this scope (RAII)
            ++guarded;
        }
    };

    // --- Fix 2: an atomic does the read-modify-write indivisibly, no lock needed. ---
    std::atomic<long> atomicCounter{0};
    auto work_atomic = [&] {
        for (int i = 0; i < kPerThread; ++i)
            ++atomicCounter;                       // one uninterruptible hardware increment
    };

    // Small helper: launch kThreads copies of fn and join them all.
    auto run = [&](auto fn) {
        std::vector<std::thread> pool;
        for (int t = 0; t < kThreads; ++t) pool.emplace_back(fn);
        for (auto& t : pool) t.join();
    };

    run(work_mutex);
    run(work_atomic);
