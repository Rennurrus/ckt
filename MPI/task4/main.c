#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    int rank;
    
    MPI_Init(&argc, &argv);
    char fname[100];
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    sprintf(fname,"io\\input_%d.txt",rank);
    FILE *fin;
    fin = fopen(fname,"r");
    int N;
    fscanf(fin,"%d",&N);
    int* a = (int*)malloc(N*sizeof(int));
    for(int i = 0; i < N; ++i){
        fscanf(fin,"%d",&a[i]);
    }
    
    int target;
    if(rank % 2 == 0){
        target = rank + 1;
    }
    else{
        target = rank - 1;
    }
    
    MPI_Status status;
    int* b = (int*)malloc(N*sizeof(int));
    printf("RANK: %d sent %d to %d\n",rank,a[0],target);
    MPI_Sendrecv(a,N,MPI_INT,target,777,b,N,MPI_INT,target,777,MPI_COMM_WORLD,&status);
    printf("RANK: %d received %d\n",rank,b[0]);
    
    MPI_File fh; 
    sprintf(fname,"io\\output_%d.txt",rank);
    MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
    char* towrite = (char*)malloc(N*sizeof(char));
    int index = 0;
    for(int i = 0; i<N; i++)
        index += snprintf(&towrite[index],N - index,"%d",b[i]);
    MPI_File_write(fh, towrite, N, MPI_CHAR, MPI_STATUS_IGNORE);
    MPI_File_close(&fh);
    
    MPI_Finalize();
    return 0;
}

