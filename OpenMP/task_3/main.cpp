#include <iostream>
#include "omp.h"

void task3(const int k) {
#pragma omp parallel num_threads(k)
    {
    printf("i am %d thread\n", omp_get_thread_num() /* Номер нити */);
    }
}

int main()
{
    int k;
    std::cin >> k;
    task3(k);
}
