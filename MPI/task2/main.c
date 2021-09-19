#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    FILE *fin;
    fin = fopen("io\\input.txt","r");
    
    int n, rank;
    fscanf(fin,"%d",&n);
    int* a = (int*)malloc(n*sizeof(int));
    for(int i = 0; i < n; ++i){
        fscanf(fin,"%d",&a[i]);
    }
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if(rank % 2 == 0){
        int sum = 0;
        for(int i = 0; i<n;i++){
            sum += a[i];
        }
        MPI_File fh; char fname[100];
        sprintf(fname,"io\\output_%d.txt",rank);
        MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
        int strSize;
        char towrite[10];
        strSize = snprintf(towrite,10,"%d",sum);
        MPI_File_write(fh, towrite, strSize, MPI_CHAR, MPI_STATUS_IGNORE);
        MPI_File_close(&fh);
    }
    else{
        float avg = 0;
        for(int i = 0; i<n;i++){
            avg += a[i];
        }
        avg /= n;
        MPI_File fh; char fname[100];
        sprintf(fname,"io\\output_%d.txt",rank);
        MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
        int strSize;
        char towrite[10];
        strSize = snprintf(towrite,10,"%lf",avg);
        MPI_File_write(fh, towrite, strSize, MPI_CHAR, MPI_STATUS_IGNORE);
        MPI_File_close(&fh);
    }
    MPI_Finalize();
    return 0;
}
