#include <iostream>
#include "omp.h"

double task11(const int N) {
    double s = 0;
#pragma omp parallel for 
    for (int i = 0; i < N; ++i) {
#pragma omp critical
        s += (4. / (1. + (((i + 0.5) * (1. / N)) * ((i + 0.5) * (1. / N)))));
    }
    return (1. / N) * s;
}

int main()
{
    int n;
    std::cin >> n;
    printf("%.g", n,task11(n));
    std::getchar();
}
