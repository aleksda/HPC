#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "mpi_count_friends_of_ten.h"
#include "functions.h"

int main(int argc, char **argv) {

    int M=0, N=0, rank, num_triple_friends;
    int **v = NULL;

    int proc_nr;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_nr);

    if(rank == 0) {
        // decide the values for M and N
        // allocate 2D array v and assign it with suitable values

        M = 20;
        N = 20;

        v = malloc(M * sizeof(*v));
        int *array = malloc(M * N * sizeof(array));

        printf("Finding tripple friends of ten for a %dx%d matrix\n", M, N);

        for(int i = 0; i < M; i++) {
            v[i] = &(array[i*N]);
        }

        int matrix[20][20] =   {{7,5,2,7,5,2,7,1,6,7,5,4,5,1,2,1,4,4,1,3},
                                {4,4,5,3,5,6,7,4,4,1,7,4,6,6,3,1,5,7,6,3},
                                {7,1,4,4,2,6,4,3,7,4,6,3,7,3,5,3,6,2,4,2},
                                {3,1,3,6,7,3,4,2,3,7,5,2,7,1,3,6,4,4,2,4},
                                {1,7,4,5,7,2,5,3,1,7,2,3,7,5,6,4,7,7,6,7},
                                {6,1,6,4,6,1,2,3,5,1,4,3,5,7,5,4,6,3,4,7},
                                {2,6,7,6,1,6,1,5,3,6,5,2,4,1,3,2,2,2,4,4},
                                {3,5,6,7,5,3,2,3,3,5,2,2,1,7,1,1,5,6,4,7},
                                {2,6,6,5,6,6,6,7,1,1,1,3,5,6,7,7,7,6,1,7},
                                {2,7,7,2,6,5,1,3,3,2,1,4,7,4,1,5,3,4,3,3},
                                {4,3,3,7,7,7,4,4,6,4,3,5,4,2,4,2,6,4,3,6},
                                {5,1,2,2,4,7,7,4,4,2,4,5,2,4,4,1,4,1,4,7},
                                {2,5,4,5,4,7,5,1,2,7,6,4,5,1,4,6,7,3,3,3},
                                {2,4,6,3,1,2,2,4,7,3,1,2,7,2,4,2,6,1,2,5},
                                {5,7,7,7,5,3,6,5,3,6,5,4,2,3,4,2,3,3,3,7},
                                {6,1,6,3,2,1,4,6,6,5,3,2,5,7,1,2,2,6,4,4},
                                {2,7,5,4,2,2,5,2,2,6,7,7,6,5,3,6,5,6,4,4},
                                {4,4,5,6,4,3,5,3,7,2,7,1,1,2,4,7,1,7,7,3},
                                {5,6,2,1,3,4,6,6,1,7,7,4,4,2,7,5,4,4,7,3},
                                {3,4,2,1,6,5,6,6,2,5,1,4,3,3,5,3,4,3,6,4}};


        for(int i = 0; i <  M; i++) {
            for(int j = 0; j < N; j++) {
                v[i][j] = matrix[i][j];
            }
        }
    }


    num_triple_friends = MPI_count_friends_of_ten(M, N, v);


    printf("MPI rank <%d>: number of triple friends=%d\n",
           rank, num_triple_friends);

    if(rank == 0) {
        // deallocation of 2D array v
        free(v[0]); free(v);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
