#include <iostream>
#include "omp.h"



double task7(const int N) {
    double s = 0;
#pragma omp parallel for reduction(+:s) 
    for (int i = 0; i < N; ++i) {
        s += (4. / (1. + (((i + 0.5) * (1. / N)) * ((i + 0.5) * (1. / N)))));
    }
    return (1. / N) * s;
}

int main()
{
    int n;
    std::cin >> n;
    printf("%.*g", n, task7(n));
}
