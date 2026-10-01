// 11_openmp_tasks.cpp — sections (a few different jobs) and tasks (recursive work, with a cutoff).
// Build (GCC/Clang):  g++ -std=c++20 -O2 -fopenmp 11_openmp_tasks.cpp -o omp_tasks
// Build (MSVC):       cl /std:c++20 /O2 /EHsc /openmp:llvm 11_openmp_tasks.cpp
//                     (plain /openmp is OpenMP 2.0 and has no `task`)
#include <cstdio>

#include "omp_compat.h"

long fib_serial(int n) { return n < 2 ? n : fib_serial(n - 1) + fib_serial(n - 2); }

// Every call spawns tasks: overhead dominates (task creation >> one addition).
long fib_task_nocutoff(int n) {
    if (n < 2) return n;
    long a, b;
    #pragma omp task shared(a)
    a = fib_task_nocutoff(n - 1);
    #pragma omp task shared(b)
    b = fib_task_nocutoff(n - 2);
    #pragma omp taskwait                 // wait for THIS node's two children
    return a + b;
}

// Granularity control: below the cutoff, plain serial recursion.
long fib_task(int n) {
    if (n < 25) return fib_serial(n);
    long a, b;
    #pragma omp task shared(a)
    a = fib_task(n - 1);
    #pragma omp task shared(b)
    b = fib_task(n - 2);
    #pragma omp taskwait
    return a + b;
}

int main() {
    // ---- sections: a small, fixed set of DIFFERENT jobs ----
    std::puts("sections:");
    #pragma omp parallel sections num_threads(3)
    {
        #pragma omp section
        std::printf("  load config     on thread %d\n", omp_get_thread_num());
        #pragma omp section
        std::printf("  open log file   on thread %d\n", omp_get_thread_num());
        #pragma omp section
        std::printf("  warm up cache   on thread %d\n", omp_get_thread_num());
    }   // implicit barrier: all three are finished here.
        // Which thread runs which section is up to the runtime (one thread may take all three).

    // ---- tasks: work whose shape is discovered at run time ----
    const int n = 32;
    long r;
    double t0 = omp_get_wtime();
    r = fib_serial(n);
    std::printf("\nserial          fib(%d) = %ld  %.1f ms\n", n, r, (omp_get_wtime() - t0) * 1e3);

    t0 = omp_get_wtime();
    #pragma omp parallel        // 1) create the team
    #pragma omp single          // 2) ONE thread starts the recursion; the others execute tasks
    r = fib_task_nocutoff(n);
    std::printf("tasks, no cutoff fib(%d) = %ld  %.1f ms  <- too fine-grained\n", n, r, (omp_get_wtime() - t0) * 1e3);

    t0 = omp_get_wtime();
    #pragma omp parallel
    #pragma omp single
    r = fib_task(n);
    std::printf("tasks, cutoff 25 fib(%d) = %ld  %.1f ms\n", n, r, (omp_get_wtime() - t0) * 1e3);
}
