#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

struct mystruct
{
    int int1;
    double double2;
    int int3;
};

int main(int argc, char** argv){
    int rank;
    int count;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &count);
    
    srand(rank);
    
    buffer = (struct user*)malloc(sizeof(struct user) * count);
    
    const int items = 3;
    MPI_Datatype users;
    MPI_Datatype types[3] = { MPI_INT, MPI_DOUBLE, MPI_INT };
    int blockLen[3] = { 1, 1, 1 };
    MPI_Aint offsets[3] = { offsetof(struct user, first), offsetof(struct user, second), offsetof(struct user, third) };
    
    MPI_Type_create_struct(items, blockLen, offsets, types, &users);
    MPI_Type_commit(&users);
    
    MPI_Finalize();
    
    return 0;
}
