#include <iostream>
#include "omp.h"

void task2(const int k) {
#pragma omp parallel num_threads(k)
    {
    int rank = omp_get_thread_num(); // Выводим номер нити
    if (!(rank % 2)) {
        printf("i am %d thread from %d threads\n", rank, omp_get_num_threads() /* Сколько всего нитей */);
    }
}
}

int main()
{
    int k;
    std::cin>>k;
    task2(k);
}
