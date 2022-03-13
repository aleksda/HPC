#include "count_mutual_links1.h"

int count_mutual_links1(int N, char **table2D, int *num_involvements) {
    /* 
     * Function: int count_mutal_links1
     * --------------------------------
     *
     * This function counts the number of mutal web links for a given
     * web-graph using the results from call to read_graph_from_file1()
     *
     * Berfore you run this function:
     * @see: void read_graph_from_file1()
     * 
     * @param int N: Value from call to read_graph_from_file1()  
     * @param char** table2D: Value from call to read_graph_from_file1() 
     * @param int* num_involvements: Allocated array of size N
     *
     * @returns: The total number of links in the web_graph (int)
     */

    // Counter-value and the number of links
	int counter, total_nr_of_links;

    // Starting from zero
    total_nr_of_links = 0;

	// couter indicates the column. Starts from zero
    counter = 0;

    /* Iterates throughout every node in the graph, then counts how many nodes
       that are linked to the current. Starts from the first element in 
       table2D, and working from there, then updating how many times a link is
       encountered */ //
	for(int i = 0; i < N; i++) {

		for(int j = 0; j < N; j++) {
            /* Here we are going to iterate ant check if we get the value 1
               For all the 1's we find, update the counter for that row */
			if(table2D[j][i] == (char) 1) {
			
                for(int k = 0; k < N; k++) {
					if(table2D[j][k] == (char) 1)
						counter++;

				} // end for k
                counter--;
			} // End if
		} // End for j

		num_involvements[i] = counter;
		total_nr_of_links  += counter;

        counter = 0; // Returning counter to zero
	} // End for i

    /* The function implemented is counting twice per linkage, therefore it is
       needed to divide the final value by two */

    // Now holds the total number of links
	return total_nr_of_links * 0.5;
} // End count_mutual_links1
