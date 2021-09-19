#include <iostream>
#include <vector>
#include <random>
#include "omp.h"

void task14(std::vector<double>& v, const int n, const int c) {
    std::vector<double> tmp(n * n);
#pragma omp parallel for num_threads(c)
    for (int k = 0; k < n * n; k++) {
        int i = k / n;
        int j = k % n;
        tmp[k] = v[n * j + i];
    }
    v.swap(tmp);
}

int main()
{
    const int range_from = -1000;
    const int range_to = 1000;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distr(range_from, range_to);
    
    double t = 0, tstart, s;
    int iterations = 500;
    int n = 1000; 
    std::vector<double> A(n*n);
    
    for (int i = 1; i <= iterations; ++i) {
        for (int i = 0; i < n; ++i) {
            A[i] = distr(mt);
        }
        tstart = omp_get_wtime();
        task14(A, n, 1);
        s = omp_get_wtime() - tstart;
        t += s;
    }
    t = t / iterations;
    printf("threads: %d exec time: %.10f\n", 1, t);
    double one_thread_exec_time = t;
    std::cout << std::fixed << "boost: " << one_thread_exec_time / t << "\n";
    
    for (int threads = 2; threads <= 8; ++threads) {
        t = 0;
        for (int i = 1; i <= iterations; ++i) {
            for (int i = 0; i < n; ++i) {
                A[i] = distr(mt);
            }
            tstart = omp_get_wtime();
            task14(A, n, threads);
            s = omp_get_wtime() - tstart;
            t += s;
        }
        t = t / iterations;
        printf("threads: %d exec time: %.10f\n", threads, t);
        t = one_thread_exec_time / t;
        std::cout << std::fixed << "boost: " << t << "\n";
    }
    
}
