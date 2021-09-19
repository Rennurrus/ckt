#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

int main(int argc, char** argv){
    int rank;
    int numtasks;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    
    char fname[100];
    sprintf(fname,"io\\input_%d.txt",rank);
    FILE *fin;
    fin = fopen(fname,"r");
    int* a = (int*)malloc(3*numtasks*sizeof(int));
    for(int i = 0; i < 3*numtasks; ++i){
        fscanf(fin,"%d",&a[i]);
    }
    
    int* recvbuf = (int*)malloc(3*numtasks*sizeof(int));
    MPI_Alltoall(a + 3*rank,3,MPI_INT,recvbuf,3,MPI_INT,MPI_COMM_WORLD);
    
    MPI_File fh;
    sprintf(fname,"io\\output_%d.txt",rank);
    MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
    char* towrite = (char*)malloc(3*numtasks*sizeof(char));
    int index = 0;
    for(int i = 0; i<(3*numtasks); i++){
        index += snprintf(&towrite[index],(3*numtasks) - index,"%d",recvbuf[i]);
    }
    MPI_File_write(fh, towrite, 3*numtasks, MPI_CHAR, MPI_STATUS_IGNORE);
    MPI_File_close(&fh);
    
    MPI_Finalize();
    
    return 0;
}
