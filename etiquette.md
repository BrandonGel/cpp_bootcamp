
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

## Asynchronous
In Lecture 5 a worker thread deposited its answer into `partials[id]` and `main` read it after joining.
That works, but it is bookkeeping. **`std::async`** does it for you: hand it a callable and it runs the
callable (potentially on a new thread) and hands back a **`std::future<T>`** — a placeholder for a value
that will exist later. Call **`.get()`** on the future and it blocks until the task is finished, then
returns the result.

Two things `std::future` gives you for free that a raw slot does not: **exceptions** thrown inside the
task are stored and re-thrown when you call `get()`, and the **synchronization** (waiting for completion)
is built in — no explicit join. Passing **`std::launch::async`** asks for the task to run on its own
thread right away, rather than possibly being deferred to run lazily inside `get()`.
- **`std::async`** - create a thread of task and return an output
- **`std::launch::async`** - ask for the task to run its own thread
- **`std::future`** - a placeholder of a variable that will exist later
- **`.get()`** - return the output from the thread
Compare this to Lecture 5's `parallel_sum`: same answer, but there is no `std::vector<std::thread>`, no
`join()` loop, and no shared `partials` array. Each `std::async` call returns a `std::future<double>`,
and summing `f.get()` over the futures both **waits** for every task and **collects** its result in one
step.

- **`std::launch::async`** forces each task onto its own thread immediately. Without it (the default,
  `async | deferred`), the implementation is *allowed* to defer the work and run it lazily inside
  `get()` — on one thread, with no parallelism. When you want real concurrency, ask for it explicitly.
- **Exceptions travel through the future.** If `partial` threw, the exception would be stored and
  re-thrown at `f.get()`, so error handling stays where you can see it instead of vanishing on a worker
  thread.
- **One caveat to remember:** the future returned by `std::async(std::launch::async, …)` blocks in its
  *destructor* until the task finishes. Keep the futures (as we do) rather than discarding them, or the
  "async" call quietly becomes blocking.
  
## Condition Threads
Threads often need to wait for each other (distribution of responsibility)
A **`std::condition_variable`** lets a thread **sleep** until another thread signals that something
changed. The consumer calls `cv.wait(lock, predicate)`: it atomically releases the mutex and sleeps, and
when notified, re-acquires the lock and checks the **predicate**; if the predicate is false it goes back
to sleep. The producer calls `cv.notify_one()` after changing the shared state to wake a waiter. The
`wait` uses a **`std::unique_lock`** (not `lock_guard`) because it must unlock and relock the mutex as it
sleeps and wakes.


## Avoiding Deadlock
**'std::scoped_lock'** -uses a deadlock-avoidance algorithm, so this is safe even though the two threads request the locks in opposite orders. 

# OpenMP Model
- A fork-join execution model
- One master thread runs sequentially; each parallel region forks a team of thread, which synchronize at an implicit barrier and join back to the master.
- Nice and easy to use rather than manually adding/forking/joining threads

## Compile /o -fopenmp and guard API class 
#ifdef _OPENMP
  #include <omp.h>
#else
  // Serial stubs — same signatures as the runtime, values for a team of one.
  inline int    omp_get_thread_num()      { return 0; }
  inline int    omp_get_num_threads()     { return 1; }
  inline int    omp_get_max_threads()     { return 1; }
  inline int    omp_get_num_procs()       { return 1; }
  inline bool   omp_in_parallel()         { return false; }
  inline void   omp_set_num_threads(int)  {}
  inline double omp_get_wtime()           { return std::chrono::duration<double>(
        std::chrono::steady_clock::now().time_since_epoch()).count(); }
#endif

## Parallel
- **`#pragma omp parallel for`** - faithfully runs the loop body on many threads — **including** the bugs. If the body updates a shared variable without saying how to combine it, you get the exact data race from Lecture 5, just with less code to write it in.
- **`reduction(op:var)`** — for combining values into one variable with an operator. Private per-thread
  copies, no synchronization in the loop, combined at the end. **Fastest and the right default here.**
- **`#pragma omp critical`** — a general critical section (one thread at a time), for updates too complex
  for a reduction. Correct, but it **serializes** every iteration and is slow in a hot loop.
- **`#pragma omp atomic`** — a lighter critical section for a *single* scalar update (`x += …`, `++x`).
  Cheaper than `critical`, but still contended if every iteration hits it.

## data-sharing clauses
- **`private(x)`** gives each thread its own *uninitialized* `x`;
- **`firstprivate(x)`** gives each thread its own copy *initialized* to the value `x` had before the region;
- **`shared(x)`** keeps one instance (which you must then synchronize if written). 
- And **`default(none)`** switches off the defaults entirely, so the compiler makes you classify every variable — the best way to
catch an accidental share.

## Loop Scheduling
`#pragma omp parallel for` has to decide *which* iterations each thread runs. The **`schedule`** clause
controls that, and the right choice depends on whether the iterations cost the same:

- **`schedule(static)`** (the usual default) splits the iterations into equal contiguous chunks, one per
  thread, decided up front. Almost no overhead — and perfect when every iteration costs the same.
  - Great for number crunching & tasks with same workload
- **`schedule(dynamic, chunk)`** hands out chunks of `chunk` iterations on demand: a thread that finishes
  early comes back for more. It balances **uneven** workloads at the cost of some run-time coordination.
  - Great for when the tasks do not have the same workload
- **`schedule(guided)`** is like dynamic but starts with large chunks and shrinks them, trading a little
  balance for less overhead.

## Nested Loops: collapse
`collapse(N)` collapses N nested loops into independent iterations and shares them across the whole team, so no thread is starved by the small outer bound/loop.
Use it when:
- the outer loop alone has **too few iterations** to occupy your threads;
- the loops are **perfectly nested** — nothing but the inner loop sits between them; and
- the iterations are **independent** (here each writes its own `a[...]`).

If the inner bound depended on the outer index (a triangular loop) or the loops were not tightly nested,
`collapse` would not apply, and you would parallelize only the outer loop.

The example runs a loop whose iteration cost **grows with the index** — iteration `i` does `O(i)` work —
so the later iterations are far heavier. Watch static fall behind.

## Performance Trap: False Sharing
Modern CPUs move memory between cores in 64-byte **cache lines**, not individual bytes. If two threads on two cores repeatedly write to *different* variables that happen to sit on the **same cache line**, each write forces the other core to reload the whole line. The variables are not logically shared, but the hardware treats the line as contended and bounces it back and forth — hence **false** sharing.
- Make sure to not modify variables on the same cache line

# Task Parallelism
## Sections
When you have a small, known number of **independent but different** pieces of work — not the same operation over an array, but genuinely separate jobs — **`#pragma omp sections`** runs them at the same time. Inside a `sections` block, each **`#pragma omp section`** is one job, handed to some thread in the team. It is the task-parallel cousin of `parallel for`: `for` runs the *same* body over many indices, `sections` runs *different* bodies once each.

`sections` needs you to write out each job in advance. **`#pragma omp task`** removes that limit: it
packages the following statement as a **unit of work** and drops it into a queue, and any idle thread in
the team picks it up. Because tasks can create *more* tasks, this is exactly what recursive,
divide-and-conquer algorithms need — the number of tasks is discovered as the recursion unfolds.
  - thread opens the socket." It does **not** scale past the number of sections you write: three sections keep at most three threads busy, no matter how many cores you have.
  - That is the key difference from `parallel for`: `for` is for the *same* work over *many* data elements and scales with the data; `sections` is for a *few* *different* pieces of work. When the number of jobs is large or only known at run time, you want the next construct instead.
The setup has a standard shape:


## Dynamic and Recursive Parallelism
- Wrap everything in a **`#pragma omp parallel`** region to create the team of threads.
- Use **`#pragma omp single`** so exactly **one** thread starts the recursion; the others wait in the team,
  ready to run the tasks it spawns.
- Inside, each recursive call becomes a `task`; **`#pragma omp taskwait`** waits for a node's child tasks
  before it combines their results.

## Granualariy (Parallelism doesn't mean better)
- Sometimes the algorithm itself is slow and has a long O() runtime
- Parallelism speeds up performance linearly, but the algorithm runtime outpaces the parallelism.


## Guide to construct `for`, `sections`, or `task`?
A quick decision guide for OpenMP's three ways to spread work:

| Construct | Use it for | Scales with |
|---|---|---|
| **`parallel for`** | the *same* operation over many data elements (a countable loop or number crunching) | the number of iterations |
| **`sections`** | a *small, fixed* set of *different* jobs, known in advance (complex) | the number of sections you write |
| **`task`** | *recursive* or *irregular* work whose size is discovered at run time (complex and uneven size) | the number of tasks created (use a cutoff) |

Most numerical kernels are `parallel for`. Reach for `sections` when you have a couple of distinct jobs to
overlap, and for `task` when the work is a tree, a graph traversal, or anything whose extent you cannot
write down as a loop.
