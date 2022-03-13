# IN3200: Home Exam Nr.1, Spring 2020

**Counting Mutual Web Linkage Occurences**

For project description click [here](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v20/teaching-material/in3200_in4200_home_exam1_v20.pdf)

## Content:
- source code

    - read_graph_from_file1.c

    - read_graph_from_file2.c

    - count_mutual_linkages1.c

    - count_mutual_linkages2.c

    - omp_count_mutual_linkages1.c

    - omp_count_mutual_linkages2.c

    - top_n_webpages.c

    - functions.c

    - main.c

    - graphs

        - example_graph.dat
        - 100nodes_graph.txt
        - web-NotreDame.txt

- Script
    - timing

    - figures
        - count_1_36k_graph.jpg
        - count_2_Amazong_graph.jpg
        - read_36k_graph.jpg

- report
    - report.pdf
    - main.tex
    - references.bib


### Disclaim:

Compile with gcc -O3 -fopenmp *.c -o run
./run -h

May vary with different compiler

or compile with make
./run -h
