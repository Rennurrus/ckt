#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    int rank,numtasks;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    if(rank != 0){
        char fname[100];
        sprintf(fname,"io\\input_%d.txt",rank);
        FILE *fin;
        fin = fopen(fname,"r");
        int N, T;
        fscanf(fin,"%d %d",&T,&N);
        printf("Rank: %d | %d %d |",rank,T,N);
        if(!T){
            int* a = (int*)malloc(N*sizeof(int));
            for(int i = 0; i < N; ++i){
                fscanf(fin,"%d",&a[i]);
                printf("%d ",a[i]);
            }
            
            MPI_Send(a,N,MPI_INT,0,T,MPI_COMM_WORLD);
        }
        else{
            double* a = (double*)malloc(N*sizeof(double));
            for(int i = 0; i < N; ++i){
                fscanf(fin,"%lf",&a[i]);
                printf("%lf ",a[i]);
            } 
            MPI_Send(a,N,MPI_DOUBLE,0,T,MPI_COMM_WORLD);
        }
        printf("\n");
    }
    else{
        MPI_Status status,st;
        
        for(int rank_index = 1; rank_index <= numtasks - 1; rank_index++){
            MPI_Probe(rank_index,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
            int length;
            if(status.MPI_TAG == 0){
                MPI_Get_count(&status,MPI_INT,&length);
                int* buffer = malloc(sizeof(int)*length);
                MPI_Recv(buffer,length,MPI_INT,rank_index,0,MPI_COMM_WORLD,&st);
                
                FILE *fout; 
                fout = fopen("io\\output.txt","a");
                for(int i = 0;i < length;++i){
                    fprintf(fout,"%d ",buffer[i]);
                }
                fprintf(fout,"\n");
            }
            else{
                MPI_Get_count(&status,MPI_DOUBLE,&length);
                double* buffer = malloc(sizeof(double)*length);
                MPI_Recv(buffer,length,MPI_DOUBLE,rank_index,1,MPI_COMM_WORLD,&st);
            
                FILE *fout; 
                fout = fopen("io\\output.txt","a");
                for(int i = 0;i < length;++i){
                    fprintf(fout,"%lf ",buffer[i]);
                }
                fprintf(fout,"\n");
            } 
        }
    }
    MPI_Finalize();
    return 0;
}
