// 10_openmp_loops.cpp — parallel for, reduction vs critical vs atomic, scheduling,
// data-sharing clauses, collapse, and false sharing.
// Build (GCC/Clang):  g++ -std=c++20 -O2 -fopenmp 10_openmp_loops.cpp -o omp_loops
// Build (MSVC):       cl /std:c++20 /O2 /EHsc /openmp:llvm 10_openmp_loops.cpp
// Without -fopenmp it still compiles (pragmas ignored, omp_compat.h stubs) and runs serially.
#include <cmath>
#include <cstdio>
#include <new>
#include <vector>

#include "omp_compat.h"

constexpr long N = 20'000'000;

template <class F>
double timed(F f) { double t0 = omp_get_wtime(); f(); return (omp_get_wtime() - t0) * 1e3; }

// Work that grows with i: iteration i costs O(i). Uneven => static scheduling is unbalanced.
double uneven_work(int i) {
    double s = 0.0;
    for (int k = 0; k < i * 40; ++k) s += std::sin(k * 1e-3);
    return s;
}

int main() {
    std::printf("threads available: %d\n\n", omp_get_max_threads());

    // ---------- 1. Combining into one variable ----------
    std::puts("Summing 1..N four ways:");
    double s_race = 0, s_crit = 0, s_atom = 0, s_red = 0;

    double ms = timed([&] {
        #pragma omp parallel for            // BUG: s_race is shared and written => data race
        for (long i = 1; i <= N; ++i) s_race += 1.0;
    });
    std::printf("  no clause : %.0f  (%.1f ms)  <- wrong when threads > 1\n", s_race, ms);

    ms = timed([&] {
        #pragma omp parallel for
        for (long i = 1; i <= N / 20; ++i) {   // 20x fewer iterations: critical is THAT slow
            #pragma omp critical
            s_crit += 1.0;
        }
    });
    std::printf("  critical  : %.0f  (%.1f ms for N/20 iterations)\n", s_crit, ms);

    ms = timed([&] {
        #pragma omp parallel for
        for (long i = 1; i <= N; ++i) {
            #pragma omp atomic
            s_atom += 1.0;
        }
    });
    std::printf("  atomic    : %.0f  (%.1f ms)\n", s_atom, ms);

    ms = timed([&] {
        #pragma omp parallel for reduction(+ : s_red)   // private copies, combined once at the end
        for (long i = 1; i <= N; ++i) s_red += 1.0;
    });
    std::printf("  reduction : %.0f  (%.1f ms)  <- correct and fastest\n\n", s_red, ms);

    // ---------- 2. Scheduling uneven work ----------
    const int M = 4000;
    std::vector<double> out(M);
    std::puts("Uneven loop (iteration i costs O(i)):");
    for (const char* label : {"static", "dynamic,16", "guided"}) {
        ms = timed([&] {
            if (label[0] == 's') {
                #pragma omp parallel for schedule(static)
                for (int i = 0; i < M; ++i) out[i] = uneven_work(i);
            } else if (label[0] == 'd') {
                #pragma omp parallel for schedule(dynamic, 16)
                for (int i = 0; i < M; ++i) out[i] = uneven_work(i);
            } else {
                #pragma omp parallel for schedule(guided)
                for (int i = 0; i < M; ++i) out[i] = uneven_work(i);
            }
        });
        std::printf("  schedule(%-10s): %.1f ms\n", label, ms);
    }

    // ---------- 3. Data-sharing clauses ----------
    std::puts("\nData-sharing clauses:");
    int base = 10;
    int last = -1;
    #pragma omp parallel for default(none) firstprivate(base) lastprivate(last) num_threads(2)
    for (int i = 0; i < 4; ++i) {
        base += i;      // each thread's own copy, starting at 10
        last = i;       // lastprivate: value from the sequentially LAST iteration is copied out
    }
    std::printf("  after loop: base = %d (unchanged), last = %d\n", base, last);

    // ---------- 4. collapse: small outer loop, many threads ----------
    const int R = 3, C = 1000;            // only 3 outer iterations
    std::vector<double> grid(R * C);
    #pragma omp parallel for collapse(2)  // 3*1000 = 3000 iterations shared across the team
    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c)
            grid[r * C + c] = r + c * 1e-3;
    std::printf("  collapse(2) filled grid, grid[last] = %.3f\n\n", grid.back());

    // ---------- 5. False sharing ----------
    // Timings here are noisy on laptops/VMs; the gap is clearest on a physical multi-core CPU
    // with several threads. Run it a few times.
    std::puts("False sharing (each thread increments ITS OWN counter):");
    const int T = omp_get_max_threads();
    const long ITERS = 50'000'000;

    struct Packed { volatile long v; };                       // 8 bytes: neighbours share a line
    struct alignas(64) Padded { volatile long v; };           // one counter per 64-byte line
    // (std::hardware_destructive_interference_size from <new> is the portable spelling of 64.)

    std::vector<Packed> packed(T);
    ms = timed([&] {
        #pragma omp parallel
        { int id = omp_get_thread_num(); for (long i = 0; i < ITERS; ++i) packed[id].v = packed[id].v + 1; }
    });
    std::printf("  packed counters : %.1f ms\n", ms);

    std::vector<Padded> padded(T);
    ms = timed([&] {
        #pragma omp parallel
        { int id = omp_get_thread_num(); for (long i = 0; i < ITERS; ++i) padded[id].v = padded[id].v + 1; }
    });
    std::printf("  padded counters : %.1f ms\n", ms);
}
