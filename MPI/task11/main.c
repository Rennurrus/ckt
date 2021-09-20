#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"
struct myarray {
    int array[3];
};

int main(int argc, char** argv){
    int rank;
    int numtasks;
    char fname[100];
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    
    const int items = 1;
    MPI_Datatype myarray3;
    MPI_Datatype types[1] = { MPI_INT };
    int blockLen[1] = { 3 };
    MPI_Aint offsets[1] = { 0 };
    
    MPI_Type_create_struct(items, blockLen, offsets, types, &myarray3);
    MPI_Type_commit(&myarray3);
    
    struct myarray* a = (struct myarray*)malloc(sizeof(struct myarray) * numtasks);
    if(rank == 0){
        sprintf(fname,"io\\input_%d.txt",rank);
        FILE *fin;
        fin = fopen(fname,"r");
        for(int i = 0; i < (numtasks-1); ++i){
            for(int j = 0; j<3;j++){
                fscanf(fin,"%d",&a[i].array[j]);
                printf("fscanf %d ",a[i].array[j]);
            }
            printf("\n");
        }
    }
    struct myarray recvbuf;
    MPI_Scatter(a,1,myarray3,&recvbuf,1,myarray3,0,MPI_COMM_WORLD);
    
    for(int j = 0; j<3;j++){
        printf("recv %d ",recvbuf.array[j]);
    }
    printf("\n");
    
    if(1){
        MPI_File fh;
        sprintf(fname,"io\\output_%d.txt",rank);
        MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
        char* towrite = (char*)malloc(3*sizeof(char));
        int index = 0;
        for(int i = 0; i<3; i++){
            index += snprintf(&towrite[index],3 - index,"%d",recvbuf.array[i]);
        }
        printf("to write %s",towrite);
        MPI_File_write(fh, towrite, 6, MPI_CHAR, MPI_STATUS_IGNORE);
        MPI_File_close(&fh);
    }
    
    MPI_Finalize();
    
    return 0;
}
