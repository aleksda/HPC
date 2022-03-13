#include "count_friends_of_ten.h"

int count_friends_of_ten(int M, int N, int **v) {
    /*
     * Function: count_friends_of_ten
     * ------------------------------
     * 
     * Takes an 2D array containing integer-values between 1-7 and returns the
     * amount of friends of 10 the array contains. A friend of 10 meaning a
     * triple of neighboring intigers whose sum equal to 10. The triple can
     * either be in the horisontal, vertical or both the diagonal directions. 
     *
     * @param int M: Integer containing the size of intex 0 of the 2D array
     * @param int M: Integer containing the size of intex 1 of the 2D array
     * @param int** v: int[][] containing the integer-values
     *
     * @returns: The number of friends of ten
     */

    // Counter-value holding the number of freinds of ten
    unsigned int counter;

    // Starting from zero
    counter = 0;

    /* Looping over each element in the matrix and checks if the current element
       added with the two next elements either in the horizontal, vertical or
       diagonal case, adds up to 10, if it does, then the counter get's 
       updated. */
    for(int m = 0; m < M; m++) {
        for(int n = 0; n < N; n++) {
            
            /* Checking for a triple of 10 in the vertical direction bellow the 
               current element */        
            m < M - 2 ? counter += (v[m][n] + v[m+1][n] + v[m+2][n] == 10) : 0;

            /* Checking for a triple of 10 in the horizontal direction starting 
               from the right (i.e current element) */ 
            n < N - 2 ? counter += (v[m][n] + v[m][n+1] + v[m][n+2] == 10) : 0;

            /* Checking for a triple of 10 in the diagonal, down to the right, 
               starting with the current element */
            m < M - 2 && n < N - 2 ? counter += (v[m][n] + v[m+1][n+1] + \
                                     v[m+2][n+2] == 10) : 0;

            /* Checking for a triple of 10 in the diagonal, down to the left, 
               starting with the current element */
            m < M - 2 && n >=    2 ? counter += (v[m][n] + v[m+1][n-1] + \
                                     v[m+2][n-2] == 10) : 0; // How about n<=2?   

        } // End for n
    } // End for m

    return counter;
} // End count_friends_of_ten
