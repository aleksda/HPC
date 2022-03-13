#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "omp.h"

#ifndef OMP_COUNT_MUTUAL_LINKS1_H
#define OMP_COUNT_MUTUAL_LINKS1_H

int omp_count_mutual_links1(int N, char **table2D, int *num_involvements);

#endif // OMP_COUNT_MUTUAL_LINKS1_H
