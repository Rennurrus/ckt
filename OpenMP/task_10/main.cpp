#include <iostream>
#include "omp.h"

void task10(const int k, const int n) {
    int s = 0;
#pragma omp parallel for num_threads(k)
    for (int i = 1; i <= n; i++) {
#pragma omp atomic
        s += i;
        printf("[%d]: Sum = %d\n", omp_get_thread_num(), s);
    }
    std::cout << "Sum = " << s;
}

int main()
{
    int k, n;
    std::cin >> k >> n;
    task10(k, n);
}
