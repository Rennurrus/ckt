#include <iostream>
#include <random>
#include <vector>
#include "omp.h"


double task12(const std::vector<double>& A, const std::vector<double>& B, const int c) {
    double s = 0;
#pragma omp parallel for reduction(+:s) num_threads(c)
    for (int i = 0; i < A.size(); i++) {
        s += A[i] * B[i];
    }
    return s;
}

int main()
{
    // generating random vectors
    const int range_from = -100;
    const int range_to = 100;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distr(range_from, range_to);
    
    double t = 0, tstart, s;
    int iterations = 5;
    int n = 10000000; // vector size
    std::vector<double> A(n);
    std::vector<double> B(n);
    
    for (int i = 1; i <= iterations; ++i) {
        // filling vectors
        for (int i = 0; i < n; ++i) {
            A[i] = distr(mt);
            B[i] = distr(mt);
        }
        //measuring time for a single threaded function
        tstart = omp_get_wtime();
        task12(A, B, 1);
        s = omp_get_wtime() - tstart;
        t += s;
    }
    t = t / iterations;
    std::cout << std::fixed << "threads: " << 1 << " exec time: " << t << "s\n";
    double one_thread_exec_time = t;
    std::cout << std::fixed << "boost: " << one_thread_exec_time / t << "\n";
    
    
    for (int threads = 2; threads <= 8; ++threads) {
        t = 0;
        for (int i = 1; i <= iterations; ++i) {
            for (int i = 0; i < n; ++i) {
                A[i] = distr(mt);
                B[i] = distr(mt);
            }
            tstart = omp_get_wtime();
            task12(A, B, threads);
            s = omp_get_wtime() - tstart;
            t += s;
        }
        t = t / iterations;
        std::cout << "threads: " << threads << " exec time: " << t  << "s\n";
        t = one_thread_exec_time / t;
        std::cout << std::fixed << "boost: " << t << "\n";
    }
}
