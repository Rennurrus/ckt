#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

int main(int argc, char** argv){
    int rank;
    int numtasks;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    
    
    int* a = (int*)malloc(sizeof(int)*numtasks);
    int* sendcounts = (int*)malloc(sizeof(int)*numtasks);
    int* displs = (int*)malloc(sizeof(int)*numtasks);
    if(rank == 0){
        FILE *fin;
        fin = fopen("io\\input.txt","r");
        int k;
        fscanf(fin,"%d",&k);
        for(int i = 0; i < k; ++i){
            fscanf(fin,"%d",&a[i]);
            sendcounts[i] = 1;
            displs[i] = numtasks - i - 1;
        }  
       
        
    }
    int recv;
    MPI_Scatterv(a,sendcounts,displs,MPI_INT,&recv,1,MPI_INT,0,MPI_COMM_WORLD);
    
    MPI_File fh; char fname[100];
    sprintf(fname,"io\\output_%d.txt",rank);
    MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
    int strSize;
    char towrite[10];
    strSize = snprintf(towrite,10,"%d ",recv);
    MPI_File_write(fh, towrite, strSize, MPI_CHAR, MPI_STATUS_IGNORE);
    MPI_File_close(&fh);
    
    MPI_Finalize();
    
    return 0;
}
