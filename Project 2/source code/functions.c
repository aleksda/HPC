#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include"functions.h"

#define randnum(min, max) ((rand() % (int) (((max)+1) - (min))) + (min))

void generate_NxM_matrix(int N, int M) {
    /*Print a random NxM list that can directly be copied and used to define
      values for a 2D array */
    printf("{");

    for(int i = 0; i < N; i++) {
        printf("{");
        for(int j = 0; j < M; j++) {
            if(j != M-1) {
                printf("%d,", (char) randnum(1, 7));
            }
            else {
                printf("%d", (char) randnum(1, 7));
            }
        }
        if(i == N-1) {
            printf("}");
        }
        else {
            printf("},\n");
        }
    }
    printf("};\n");
} // End void generate_NxM_matrix

int **generate_NxM_array(int N, int M) {
    /*Print a random NxM list that can directly be copied and used to define
      values for a 2D array */

    int *T = (int*)malloc(N * M * sizeof(int));
    int **table = (int**)malloc(N * sizeof(int*));

    for(int i = 0; i < N; i++){
        table[i] = &(T[i * M]);
    } // End for

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            table[i][j] = (int) randnum(1,7);
        } // End for j
    } // End for i
    return table;
} // End void generate_NxM_array

