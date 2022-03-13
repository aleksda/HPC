#include "count_mutual_links2.h"

int omp_count_mutual_links2(int N, int N_links, int *row_ptr, 
                        int *col_idx, int *num_involvements) {
    /* 
     * Function: int count_mutal_links2
     * --------------------------------
     *
     * This function counts the number of mutal web links for a given
     * web-graph using the results from call to read_graph_from_file2()
     *
     * Berfore you run this function:
     * @see: void read_graph_from_file2()
     * 
     * @param int N: Value from call to read_graph_from_file2() 
     * @param int N_links: Value from call to read_graph_from_file2() 
     * @param int* row_ptr: Value from call to read_graph_from_file2() 
     * @param int* col_idx: Value from call to read_graph_from_file2() 
     * @param int* num_involvements: Allocated array of size N
     *
     * @returns: The total number of links in the web_graph (int)
     */

    int i, j; // Iterators
	unsigned int total_nr_of_links; // Counter-value for the number of links

    // Starting from zero
    total_nr_of_links = 0;

    /* Iterates throughout every node in the graph and updates the amount of
       elements in each of the rows containing the value 1 for that specific
       column.*/

    /* Using OpenMP for parallelization */
	#pragma omp parallel for reduction(+:total_nr_of_links,num_involvements[:N])
	for (i = 0; i < N; i++) {
        /* Checks for > 1 elements in each of the rows then updates the
           total_nr_of_links variable for columns with linkages */
		if ((row_ptr[i + 1] - row_ptr[i]) > 1) {
			for (j = row_ptr[i]; j < row_ptr[i + 1]; j++) {
				num_involvements[col_idx[j]] += (row_ptr[i+1] - row_ptr[i]) - 1;
				total_nr_of_links += (row_ptr[i + 1] - row_ptr[i]) - 1;
			} // End for j
		} // End if

	} // End for i

    /* The function implemented is counting twice per linkage, therefore it is
       needed to divide the final value by two */

    // Now holds the total number of links
	return total_nr_of_links * 0.5;

} // End omp_count_mutual_links2
