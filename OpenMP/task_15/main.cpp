#include <stdio.h>
#include <iostream>
#include <string>
#include "omp.h"

long long task15(int n,int c) {
    int i,j;
    if(n<2)
        return n;
    else {
#pragma omp task shared(i) 
        i=task15(n-1,c);
#pragma omp task shared(j)
        j=task15(n-2,c);
#pragma omp taskwait
        return i+j;
    }
}
int main()  
{
    double t = 0, tstart, s;
    int iterations = 10;
    int n = 37; 
    omp_set_num_threads(1);
    for (int i = 1; i <= iterations; ++i) {
        tstart = omp_get_wtime();
        task15(n,1);
        s = omp_get_wtime() - tstart;
        t += s;
    }
    t = t / iterations;
    printf("threads: %d exec time: %.10f\n", 1, t);
    double one_thread_exec_time = t;
    std::cout << std::fixed << "boost: " << one_thread_exec_time / t << "\n";
    
    for (int threads = 2; threads <= 8; ++threads) {
        t = 0;
        omp_set_num_threads(threads);
        for (int i = 1; i <= iterations; ++i) {
            tstart = omp_get_wtime();
            task15(n,threads);
            s = omp_get_wtime() - tstart;
            t += s;
        }
        t = t / iterations;
        printf("threads: %d exec time: %.10f\n", threads, t);
        t = one_thread_exec_time / t;
        std::cout << std::fixed << "boost: " << t << "\n";
    }
}

