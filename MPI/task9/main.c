#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

int main(int argc, char** argv){
    int rank,numtasks;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    
    char fname[100];
    sprintf(fname,"io\\input_%d.txt",rank);
    FILE *fin;
    fin = fopen(fname,"r");
    int* a = (int*)malloc((numtasks+5)*sizeof(int));
    for(int i = 0; i<(numtasks+5);++i){
        fscanf(fin,"%d",&a[i]);
    }
    printf("\n");
    
    int* min = (int*)malloc((numtasks+5)*sizeof(int));
    MPI_Reduce(a,min,numtasks+5,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);
    
    if(rank == 0){
        FILE *fout;
        sprintf(fname,"io\\output_%d.txt",rank);
        fout = fopen(fname,"w");
        for(int i = 0; i<(numtasks+5);++i){
            fprintf(fout,"%d ",min[i]);
        }
    }
    
    MPI_Finalize();
    
    return 0;
}
