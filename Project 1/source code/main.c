#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "read_graph_from_file1.h"
#include "read_graph_from_file2.h"
#include "count_mutual_links1.h"
#include "count_mutual_links2.h"
#include "omp_count_mutual_links1.h"
#include "omp_count_mutual_links2.h"
#include "top_n_webpages.h"
#include "functions.h"
#include "tests.h"
#include "omp.h"

int main(int argc, char *argv[]) {

     // Number of nodes, 
    int N, N_links, total_nr_of_links;
    char **array; // 2D Array storing the data

    int *num_involvements; // Storing the number of involvements

    int mutal_links; // Number of mutal linkages in the web-graph

    char arg; 

    bool test, seq, paral, help;

	int *row_ptr;
	int *col_idx;

    //clock_t start;
    double start;    

    char *filename; // Filename of the webgraph
    //filename = argv[1];

    test  = 0;
    seq   = 0;
    paral = 0;
    help  = 0;

    srand(time(0));

	while((arg = getopt(argc, argv, "tsph")) != EOF) {

		switch(arg) {

			case 't':
				test = 1;
                filename = "graphs/example_graph.dat";
				break;

			case 's':
				seq = 1;
                filename = argv[2];
				break;

			case 'p':
				paral = 1;
                filename = argv[2];
				break;

            case 'h':
                help = 1;
                break;

			default:
        exit(-1);
		}
	}

    if(argc == 1) {
        printf("Error!\nTo few commandline-arguments given! Use the flag");
        printf(" [-h] for help!\n");

    } else if(test == 1) {

        /* NB: Works perfectly fine! However, due to the way the programs are
           implemented,  running all the tests at once may not work */

        test_read_graph_from_file1();
        //test_read_graph_from_file2();

        test_count_mutual_links1();
        //test_count_mutual_links2();
        test_omp_count_mutual_links1();
        //test_omp_count_mutual_links2();

        test_top_n_webpages();


    } else if(seq == 1) {

        start = clock();

        read_graph_from_file1(filename, &N, &array);
	    //printf("Completed read_graph_from_file1 after %.15f seconds.\n", 
          //     ((double)(clock() - start))/CLOCKS_PER_SEC);

        num_involvements = (int*)malloc(N * sizeof(int));

        mutal_links = omp_count_mutual_links1(N, array, num_involvements);
        printf("Total number of mutal links is %d\n", mutal_links);
        
	    printf("Completed count_mutual_links1 after %.15f seconds.\n", 
               ((double)(clock() - start))/CLOCKS_PER_SEC);
        //top_n_webpages(N, num_involvements, 8);

        free(num_involvements);

    } else if(paral == 1) {

        start = omp_get_wtime();

        read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

		num_involvements = (int*)malloc(N * sizeof(int));

		mutal_links = omp_count_mutual_links2(N, N_links, row_ptr, 
                                          col_idx, num_involvements);
		printf("Total number of mutal links is %d\n", mutal_links);

	    printf("Completed count_mutual_links1 after %.15f seconds.\n", 
               (omp_get_wtime() - start));

        free(num_involvements);

    } else if(help == 1) {
        printf("Usage: Provide either the following flag [-t], [-s], [-p] ");
        printf("as the first\ncommandline-argument. If either [-s] or [-p] ");
        printf("is chosen, supply a filename\ncontaining a graph as the ");
        printf("second commandline-argument.\n\n");

        printf("For [-t] running the following files\n");
        printf("test_read_graph_from_file1 \ntest_read_graph_from_file2");
        printf("test_count_mutal_links1 \ntest_count_mutal_links2\n\n");

        printf("For [-s] running the following files\n");
        printf("read_graph_from_file1 \ncount_mutal_links1\n");
        printf("top_n_webpages\n\n");

        printf("For [-p] running the following files\n");
        printf("read_graph_from_file2 \nOMP_count_mutal_links2\n");

    } else {

        printf("Error!");

    }

    return 0;
} 

