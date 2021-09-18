#include <stdio.h>
#include "omp.h"

void task1() 
{
#pragma omp parallel num_threads(4) // Всего 4 нити
    {
    printf("Hello World\n");
    }
}

int main()
{
    task1();
}

