# IN3200: Home Exam Nr.2, Spring 2020

**finding “triple-friends of 10”**

**Candidate 15113**

For project description click [here](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v20/teaching-material/in3200_in4200_home_exam2_v20.pdf)

## Content:

- source code
    - [count_frineds_of_ten.c]
        - File containing the code finding friends of ten
    - [count_frineds_of_ten.h]
        - Header for count_friends_of_ten.c
    - [mpi_count_frineds_of_ten.c]
        - File containing the code for the parallelized version of finding friends of ten
    - [mpi_count_frineds_of_ten.h]
        - Header for mpi_count_frineds_of_ten.c
    - [serial_main.c]
        - Main program for the serial code
    - [mpi_main.c]
        - Main program for the parallel code
    - [functions.c]
        - File containing helper functions
    - [functions.h]
        - Header for functions.c

### Disclaimer:

In order to compile the the programs. Run 'make serial.x' for compiling the serial version, or run 'make parallel.x' for compiling the parallel version.
Then, in order to run the programs, type './serial.x' then enter to run the serial program, or 'mpirun -np x ./parallel.x' where 'x' is the number of threads, in order to run the parallel version.

Note: This has to be done in the 'source code' directory
