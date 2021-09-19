#include <iostream>
#include <vector>
#include "omp.h"
#include <random>
#include <algorithm>

int part(std::vector<int>& v, int low, int high){
    int pivot = v[high];
    int i = low - 1;
    for(int j = low; j <= high - 1;j++){
        if(v[j] <= pivot){
            i++;
            std::swap(v[i],v[j]);
        }
    }
    std::swap(v[i+1],v[high]);
    return (i+1);
}

void task16(std::vector<int>& v, int low, int high) {
    if(low < high){
        int p = part(v,low,high);
        
#pragma omp task shared(v) firstprivate(low,p)
        task16(v, low, p - 1);
#pragma omp task shared(v) firstprivate(high,p)
        task16(v, p + 1, high);
    }
#pragma omp taskwait
}

int main () {
    const int range_from = -1000;
    const int range_to = 1000;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distr(range_from, range_to);
    
    double t = 0, tstart, s;
    int iterations = 5;
    int n = 5000000; 
    std::vector<int> A(n);
    for(int threads = 2;threads <= 8;threads++){
        for(int iteration = 1; iteration <= iterations; iteration++){
            for (int i = 0; i < n; ++i) {
                A[i] = distr(mt);
            }
            
            tstart = omp_get_wtime();
            
#pragma omp parallel num_threads(threads)
            {
#pragma omp single nowait
                task16(A,0,A.size() - 1);
            }
            
            s = omp_get_wtime() - tstart;
            t += s;
        }
        t = t / iterations;
        printf("threads: %d exec time: %.10f\n", threads ,t);
        t = 6.4833999634 / t;
        std::cout << std::fixed << "boost: " << t << "\n";
    }
}
