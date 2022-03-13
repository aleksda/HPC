#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "read_graph_from_file2.h"

void read_graph_from_file2(char *filename, int *N, int *N_links, 
                           int **row_ptr, int **col_idx) {

	/* 
     * Function: void read_graph_from_file2
     * ------------------------------------
     *
     * This function reads a file containing a web-graph, then stores all
     * the information about the web-graph using the CRS format.
     *
     * Go hto this link for information about the format of the web-graph
     * @see: https://snap.stanford.edu/data/web-NotreDame.html
     * 
     * @param char* filename: Pointer to the filename of the web-graph
     * @param int* N: Stores the value of the number of nodes in the web-graph
     * @param int* N_links:  Stores the number of web linkages
     * @param int** row_ptr: Stores col_idx values row by row (dissect)
     * @param int** col_idx: Stores column indices to all the direct links
     */

    int nr_of_edges; // Variable storing the number of edges in the web-graph
    int n1, n2; // Variables storing the data values

    // Counter values
    int val;        // Counter for iterating through arrays of size N_link
    int *val_arr;   // Counter than ensures no updates in arrays

    // FromNodeId & ToNodeId
    int *from_array, *to_array; // To & from ID arrays

    // Open the file for reading
	FILE* data_ptr;

    data_ptr= fopen(filename, "r");
    if(data_ptr == NULL){
        printf("Could not find file! Make sure to add a file as an argument\n");
        exit(-1);
    } // End if

    // The line printed bellow this line is data taken from the file
    printf("Data from the file: \n");

    /* Skipping the first two lines of the web-graph as they do not contain
       any data that needs to be processed */
    for(int i = 0; i < 2; i++) {
        fscanf(data_ptr, "%*[^\n]\n");
    }// End for

    /* Assigning the values for N and nr_of_edges as line 3 in the web-graph
       this information */
    fscanf(data_ptr, "%*s %*s %d %*s %d \n", N, N_links);

    // Reading the number of nodes and edges
    //fscanf(data_ptr, "# Nodes: %d Edges: %d\n", N, N_links);

    // Printing the number of Nodes and Edges of the web-graph to the terminal
    printf("Nodes: %d, Edges: %d\n", *(N), *N_links);

    // Allocating the memory for row_ptr and col_idx
    *(row_ptr) = (int*)malloc(*((N) + 1) * sizeof(int));
    *(col_idx) = (int*)malloc(*(N_links) * sizeof(int));

    // Skip line 4 as it does not contain data to be processed
    fscanf(data_ptr, "%*[^\n]\n");

    // Allocating size of from and to_array
    from_array = (int*)malloc(*(N_links) * sizeof(int));
    to_array   = (int*)malloc(*(N_links) * sizeof(int));

    // Allocating val_arr 
    val_arr = (int*)malloc(*(N) * sizeof(int));

	//Filling the row_ptr array with zeros
	/*for (int i = 0; i < *(N)+1; i++) // Not necessary ?
		(*row_ptr)[i] = (char) 0; */

	// Counter for updating values in arrays
    val = 0; // From 0 to number of lines in the graph (N_links)

    /* Reads the remaining data and counts the number of occurrences for
       each value in to_array */
    while (fscanf(data_ptr, "%i\t%i \n", &n1, &n2) != EOF) {
        if(n1 != n2) {
		    (*row_ptr)[n2+1]++;
            to_array[val] = n2; from_array[val] = n1; // NB: Two operations

            val++; // Updates the counter
        } // End if
    } // End while

    // Formating array with gradual addition
	for (int i = 1; i < *(N)+1; i++) {
		(*row_ptr)[i] += (*row_ptr)[i-1];
	} // End for


    /* Iterates over links to find each index for the column array. We need a 
       counter so that we can keep track of all the rows */
    for(int i = 0; i < val; i++) {
        (*col_idx)[val_arr[to_array[i]] + (*row_ptr)[to_array[i]]] \
                                        = from_array[i];
        val_arr[to_array[i]]++;
  } // End for 

    // Finalize & close file
	free(from_array); free(to_array); free(val_arr);
	fclose(data_ptr);

} // End read_graph_from_file2 

