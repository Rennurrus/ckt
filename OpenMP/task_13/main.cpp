#include <iostream>
#include <vector>
#include "omp.h"
#include <random>
#include <algorithm>

int task13(const std::vector<int>& A, const int c) {
    double max = A[0];
#pragma omp parallel for reduction(max:max) num_threads(c)
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] > max)
        {
            max = A[i];            
        }
    }
    
    return max;
}

int main()
{
    const int range_from = -1000;
    const int range_to = 1000;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distr(range_from, range_to);
    
    double t = 0, tstart, s;
    int iterations = 50;
    int n = 10000000; 
    std::vector<int> A(n);
    
    
    for (int i = 1; i <= iterations; ++i) {
        for (int i = 0; i < n; ++i) {
            A[i] = distr(mt);
        }
        tstart = omp_get_wtime();
        task13(A, 1);
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
            task13(A, threads);
            s = omp_get_wtime() - tstart;
            t += s;
        }
        t = t / iterations;
        printf("threads: %d exec time: %.10f\n", threads ,t);
        t = one_thread_exec_time / t;
        std::cout << std::fixed << "boost: " << t << "\n";
    }
}

