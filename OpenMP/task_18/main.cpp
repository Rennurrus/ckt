#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <omp.h>
int inf = 100000000;

std::vector < std::vector < std::pair<int, int> > > loadGraph() {
    std::fstream inputf("test7.txt");
    int n, x;
    inputf >> n;
    std::vector < std::vector < std::pair<int, int> > > g;
    std::vector < std::pair<int, int> > temp;
    std::vector<int> answ(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputf >> x;
            if (x != 0) {
                temp.push_back(std::make_pair(j, x));
            }
        }
        g.push_back(temp);
    }
    return g;
}

std::vector<int> Dijkstra(std::vector < std::vector < std::pair<int, int> > > g, int s, int threads) {
    int n = g.size();
    std::vector<int> d(n, inf);
    d[s] = 0;
    std::vector<char> u(n);
    for (int i = 0; i < n; ++i) {
        int v = -1;
#pragma omp parallel for num_threads(threads)
        for (int j = 0; j < n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == inf)
            break;
        u[v] = true;
#pragma omp parallel for num_threads(threads)
        for (int j = 0; j < g[v].size(); ++j) {
            int to = g[v][j].first, len = g[v][j].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
            }
        }
    }
    return d;
}

int main() {
    std::vector < std::vector < std::pair<int, int> > > G;
    double t = 0, tstart, s;
    int iterations = 5;
    for (int i = 1; i <= iterations; ++i) {
        G = loadGraph();
        tstart = omp_get_wtime();
        Dijkstra(G, 0, 1);
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
            Dijkstra(G, 0, threads);
            s = omp_get_wtime() - tstart;
            t += s;
        }
        t = t / iterations;
        printf("threads: %d exec time: %.10f\n", threads, t);
        std::cout << std::fixed << "boost: " << one_thread_exec_time / t << "\n";
    }
}
