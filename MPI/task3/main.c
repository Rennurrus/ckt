#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    FILE *fin;
    fin = fopen("io\\input.txt","r");
    
    int n, rank, numtasks, rc;
    double a[12];
    fscanf(fin,"%d",&n);
    for(int i = 0; i < n; ++i){
        fscanf(fin,"%lf",&a[i]);
    }
    
    MPI_Status status;
    char *buf;
    int bufsize;
    
    MPI_Init(&argc, &argv);
    
    MPI_Pack_size(n, MPI_DOUBLE, MPI_COMM_WORLD, &bufsize);
    bufsize += n*MPI_BSEND_OVERHEAD;
    buf = (char *)malloc( bufsize );
    MPI_Buffer_attach( buf, bufsize );
    
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    if(rank == 0){
        for(int i = numtasks - 1, j = 0;i>0 && j<n;--i,j++){
            MPI_Bsend(&a[j],1,MPI_DOUBLE,i,777,MPI_COMM_WORLD);
        }
    }
    else{
        double inmsg;
        MPI_Recv(&inmsg,1,MPI_DOUBLE,0,777,MPI_COMM_WORLD,&status);
        
        MPI_File fh; char fname[100];
        sprintf(fname,"io\\output_%d.txt",rank);
        MPI_File_open(MPI_COMM_SELF, fname,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
        int strSize;
        char towrite[10];
        strSize = snprintf(towrite,10,"%lf",inmsg);
        MPI_File_write(fh, towrite, strSize, MPI_CHAR, MPI_STATUS_IGNORE);
        MPI_File_close(&fh);
    }
    
    MPI_Finalize();
    return 0;
}

