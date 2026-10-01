// omp_compat.h — lets OpenMP code compile and run serially WITHOUT -fopenmp.
// Uses classic #ifndef guards (portable everywhere) rather than #pragma once, for contrast.
#ifndef CPP_BOOTCAMP_OMP_COMPAT_H
#define CPP_BOOTCAMP_OMP_COMPAT_H

#ifdef _OPENMP          // defined by the compiler only when OpenMP is enabled
  #include <omp.h>
#else
  #include <chrono>
  // Serial stubs: same signatures as the OpenMP runtime, values for a "team of one".
  // Unknown #pragma omp lines are simply ignored by the compiler in this mode.
  inline int    omp_get_thread_num()     { return 0; }
  inline int    omp_get_num_threads()    { return 1; }
  inline int    omp_get_max_threads()    { return 1; }
  inline int    omp_get_num_procs()      { return 1; }
  inline int    omp_in_parallel()        { return 0; }   // real API returns int
  inline void   omp_set_num_threads(int) {}
  inline double omp_get_wtime() {
      return std::chrono::duration<double>(
                 std::chrono::steady_clock::now().time_since_epoch()).count();
  }
#endif

#endif  // CPP_BOOTCAMP_OMP_COMPAT_H
