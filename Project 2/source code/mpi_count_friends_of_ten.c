#include "mpi_count_friends_of_ten.h"

int MPI_count_friends_of_ten(int M, int N, int **v) {
    /*
     * Function: MPI_count_friends_of_ten
     * ------------------------------
     * 
     * Takes an 2D array containing integer-values between 1-7 and returns the
     * amount of friends of 10 the array contains. A friend of 10 meaning a
     * triple of neighboring intigers whose sum equal to 10. The triple can
     * either be in the horisontal, vertical or both the diagonal directions. 
     *
     * This function is a parallelized version of count_friends_of_ten, where
     * MPI was used.
     *
     * @param int M: Integer containing the size of intex 0 of the 2D array
     * @param int M: Integer containing the size of intex 1 of the 2D array
     * @param int** v: int[][] containing the integer-values
     *
     * @returns: The number of friends of ten
     */

    // The variables which will be used
    int counter, rank, proc_nr, M_per_worker, M_rest, Mgpt, 
        gpt, start, tot_nr_of_friends;

    // Friends of ten per worker
    counter = 0;

    // Using MPI to get rank and size (proc_nr)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_nr);

    // Hold for all threads
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // For the master thread
    if(rank == 0) {

        start = 0;

        // For distribution. N could have also been used
        M_per_worker = M / proc_nr;
        M_rest       = M % proc_nr;

        // For-loop prepares chunks to be sent to other workers
        for(int i = 1; i < proc_nr; i ++) { // i is one worker

            /* Adds ghost points. Value 1 for top worker. Or the value 2
               othervise. Split rows per worker*/
            gpt = (i == 1) ? 1 : 2;
            Mgpt = M_per_worker + gpt;

            // Sends data to the other workers
            MPI_Send(&gpt, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&Mgpt, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&v[start][0], Mgpt*N, MPI_INT, i, 0, MPI_COMM_WORLD);

            // Pushes row for next point
            start += Mgpt - gpt;
        } // End for i

        int thread_row = M_per_worker + M_rest + 1;

        // Allocates array for the master thread 
        int** v0    = malloc(thread_row * sizeof(int*));
        int* v_ptr  = malloc(thread_row * N * sizeof(int));

        for(int i = 0; i < thread_row; i++)
            v0[i] = &(v_ptr[i*N]);

        // Now storing values for v0
        for(int m = 0; m < thread_row; m++) {
            for(int n = 0; n < N; n++) {

                v0[m][n] = v[m + M_per_worker*(proc_nr - 1)-1][n];
            } // End for n
        } // End for m

        // Updating value for counter (master thread)
        for(int m = 0; m < thread_row; m++) {
            for(int n = 0; n < N; n++) {

                /* Checking for a triple of 10 in the vertical direction bellow the 
                   current element */  
                m < thread_row - 2  ? counter += (v0[m][n] + \
                                        v0[m+1][n] + v0[m+2][n] == 10) : 0;

                /* Checking for a triple of 10 in the horizontal direction starting 
                   from the right (i.e current element) */ 
                n < N - 2 && m != 0 ? counter += (v0[m][n] + \
                                        v0[m][n+1] + v0[m][n+2] == 10) : 0;

                /* Checking for a triple of 10 in the diagonal, down to the right, 
                   starting with the current element */
                m < thread_row - 2 && n < N - 2 ? counter += (v0[m][n] + \
                                        v0[m+1][n+1] + v0[m+2][n+2] == 10) : 0;

                /* Checking for a triple of 10 in the diagonal, down to the left, 
                   starting with the current element */
                m < thread_row - 2 && n >=    2 ? counter += (v0[m][n] + \
                                        v0[m+1][n-1] + v0[m+2][n-2] == 10) : 0;

            } // End for n
        } // End for m

        // Finalize
        free(v0[0]); free(v0);
    } // End if

    // For Worker threads
     if(rank > 0) {

        // Receiving Data from waster thread  
        MPI_Recv(&gpt, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&Mgpt, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Allocating the array we need (based on the information)
        v  = malloc(Mgpt * sizeof(int*));
        int* v_ptr = malloc(Mgpt * N * sizeof(int));

        // Createing sub-array
        for(int i = 0; i < Mgpt; i++)
            v[i] = &(v_ptr[i*N]);

        // Receiving array from master
        MPI_Recv(&(v[0][0]), Mgpt*N, MPI_INT, 0, 0, 
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Updating value for counter (master thread)
        for(int m = 0; m < Mgpt; m++) {
            for(int n = 0; n < N; n++) {

                /* Checking for a triple of 10 in the vertical direction bellow the 
                   current element */  
                m < Mgpt - 2 ? counter += (v[m][n] + v[m+1][n] + \
                                                     v[m+2][n] == 10) : 0;

                /* Checking for a triple of 10 in the diagonal, down to the right, 
                   starting with the current element */
                m < Mgpt - 2 && n < N - 2 ? counter += (v[m][n] + \
                                     v[m+1][n+1] + v[m+2][n+2] == 10) : 0;

                /* Checking for a triple of 10 in the diagonal, down to the left, 
                   starting with the current element */
                m < Mgpt - 2 && n >=    2 ? counter += (v[m][n] + \
                                     v[m+1][n-1] + v[m+2][n-2] == 10) : 0;

                /* Checking for a triple of 10 in the horizontal direction starting 
                   from the right (i.e current element) */ 
                if(rank == 1) { // Making sure to avoind double counting 
                    n < N - 2 && m != Mgpt - 1 ? counter += (v[m][n] + \
                                         v[m][n+1] + v[m][n+2] == 10) : 0;
                } else {
                    n < N - 2 && m != Mgpt - 1 && m != 0 ? counter += \
                              (v[m][n] + v[m][n+1] + v[m][n+2] == 10) : 0;
                } // End if rank
            } // end n
        } // End m

        // Finalize
        free(v[0]); free(v);

    } // End if
    
    // Shares the friends of ten between the threads
    MPI_Allreduce(&counter, &tot_nr_of_friends, proc_nr, 
                  MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Returning the number of friends of 10
    return tot_nr_of_friends;
} // End MPI_count_friends_of_ten
