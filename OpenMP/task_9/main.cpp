#include <iostream>
#include "omp.h"

void task9(const int k) {
#pragma omp parallel num_threads(k)
    {
#pragma omp sections 
        {
#pragma omp section
            {
            printf("[%d]: came in section 1\n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("[%d]: came in section 2\n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf("[%d]: came in section 3\n", omp_get_thread_num());
        }
    }
    printf("[%d]: parallel region\n", omp_get_thread_num());
}
}

int main()
{
    int k;
    std::cin >> k;
    task9(k);
}
