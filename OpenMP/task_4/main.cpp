#include <iostream>
#include "omp.h"

//1
int main()
{
    int n, sum = 0, psum;

    int k;
    scanf_s("%d", &k);
    scanf_s("%d", &n);

    
    #pragma omp parallel reduction(+:sum) /*Переменная sum является частной для потоков*/ num_threads(2) private(psum) /*Каждый поток содержит свой psum*/
    {
        psum = 0;
        if (omp_get_thread_num() == 0) // Первая половина
            for (int i = 1; i <= n / 2; i++)
                psum += i;
        else
        if (omp_get_thread_num() == 1) // Вторая половина
            for (int i = n / 2 + 1; i <= n; i++)
                psum += i;

        sum += psum;
        printf_s("[%d]: Sum = %d\n", omp_get_thread_num(), psum);
    }
}

//2
/*int main(){
    #pragma omp parallel reduction(+:sum) num_threads(k) private(psum)
    {
        psum = 0; 
        int step = n / omp_get_num_threads();
        for (int i = omp_get_thread_num() * step + 1; i <= omp_get_thread_num() * step + step; ++i) {
            psum += i;
        }

        int max = (omp_get_num_threads() - 1) * step + step;
        if (n != max) {
            int i = max + omp_get_thread_num() + 1;
            if (i <= n) {
                psum += i;
            }
        }

        sum += psum;
        printf_s("[%d]: Sum = %d\n", omp_get_thread_num(), psum);
    }

    printf("Sum = %d\n", sum);
}*/