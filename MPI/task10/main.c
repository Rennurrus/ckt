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
    MPI_Allreduce(a,min,numtasks+5,MPI_INT,MPI_PROD,MPI_COMM_WORLD);
    
    MPI_File fh; 
    sprintf(fname,"io\\output_%d.txt",rank);
    MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
    char* towrite = (char*)malloc((numtasks+5)*sizeof(char));
    int index = 0;
    for(int i = 0; i<(numtasks+5); i++)
        index += snprintf(&towrite[index],(numtasks+5) - index,"%d ",min[i]);
    MPI_File_write(fh, towrite, (numtasks+5), MPI_CHAR, MPI_STATUS_IGNORE);
    MPI_File_close(&fh);
    
    MPI_Finalize();
    
    return 0;
}
