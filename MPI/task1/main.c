#include "mpi.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
    FILE *fin;
    fin = fopen("io\\input.txt","r");
    
    int x;      // Целое число
    int rank;   // Процесс 
    float y;    // Вещественное число
    fscanf(fin,"%d %f",&x,&y); // Считываем числа
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if(rank % 2 == 0)   // Если процесс по номеру делится на 2
    {
        printf("%d\n",x);   // Выводим целое
        MPI_File fh; char fname[100];
        sprintf(fname,"io\\output_%d.txt",rank);
        MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
        int strSize;
        char towrite[10];
        strSize = snprintf(towrite,10,"%d",x);
        MPI_File_write(fh, towrite, strSize, MPI_CHAR, MPI_STATUS_IGNORE);
        MPI_File_close(&fh);
    }
    else                // Если процесс по номеру не делится на 2
    {
        printf("%f\n",y); // Выводим вещественное
        
        MPI_File fh; char fname[100];
        sprintf(fname,"io\\output_%d.txt",rank);
        MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
        int strSize;
        char towrite[10];
        strSize = snprintf(towrite,10,"%f",y);
        MPI_File_write(fh, towrite, strSize, MPI_CHAR, MPI_STATUS_IGNORE);
        MPI_File_close(&fh);
    }
    MPI_Finalize();
    return 0;
}
