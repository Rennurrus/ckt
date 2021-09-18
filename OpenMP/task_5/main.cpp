#include <iostream>
#include "omp.h"

void task5(const int k, const int n) {
    int s = 0;
#pragma omp parallel for reduction(+:s) num_threads(k) schedule(guided,2)
    for (int i = 1; i <= n; i++) {
        s += i;
        printf("[%d]: Sum = %d\n", omp_get_thread_num(), s);
        //printf("[%d]: calculation of the iteration number %d\n", omp_get_thread_num(), i);
    }
    std::cout << "Sum = " << s;
}


int main()
{
    int k, n;
    std::cin >> k >> n;
    task5(k, n);
}
