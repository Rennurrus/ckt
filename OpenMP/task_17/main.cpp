#include<iostream>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <omp.h>
int inf = 1000000000;

std::vector<std::vector<int> > loadGraph(){
    std::fstream inputf("test7.txt");
    int n;
    inputf >> n;
    std::vector<std::vector<int> > a(n, std::vector <int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inputf >> a[i][j];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                a[i][j] = a[i][j] == 0 ? inf : a[i][j];
            }
        }
    }
    return a;
}

void Floyd(std::vector<std::vector<int> >& g, int threads) {
#pragma omp parallel for num_threads(threads)
    for (int k = 0; k < g.size(); k++) {
        for (int i = 0; i < g.size(); i++) {
            for (int j = 0; j < g.size(); j++) {
                if (g[i][j] > g[i][k] + g[k][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
    }
}

int main () {
    std::vector<std::vector<int> > G;
    double t = 0, tstart, s;
    int iterations = 5;
    for (int i = 1; i <= iterations; ++i) {
        G = loadGraph();
        tstart = omp_get_wtime();
        Floyd(G,1);
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
            G = loadGraph();
            tstart = omp_get_wtime();
            Floyd(G,threads);
            s = omp_get_wtime() - tstart;
            t += s;
        }
        t = t / iterations;
        printf("threads: %d exec time: %.10f\n", threads, t);
        std::cout << std::fixed << "boost: " << one_thread_exec_time / t << "\n";
    }
}

