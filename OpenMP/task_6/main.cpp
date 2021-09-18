#include <iostream>
#include "omp.h"

int main()
{
    int k = 4, n = 10, sum = 0, psum;

    #pragma omp parallel reduction(+:sum) num_threads(k) private(psum)
        {
            psum = 0;
            #pragma omp for schedule (static) // распаралелирование цикла for
            //#pragma omp for schedule (static, 1)
            //#pragma omp for schedule (static, 2)
            //#pragma omp for schedule (dynamic)
            //#pragma omp for schedule (dynamic, 2)
            //#pragma omp for schedule (guided)
            //#pragma omp for schedule (guided, 2)
                for (int i = 1; i <= n; i++) 
                {
                    psum = psum + i;
                    printf_s("[%d]: calculation of the iteration number %d\n", omp_get_thread_num(), i);
                }

            sum += psum;
            printf_s("[%d]: Sum = %d\n", omp_get_thread_num(), psum);
        }
    printf_s("Sum = %d\n", sum);
}