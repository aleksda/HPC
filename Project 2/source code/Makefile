serial_flags = gcc -std=c11 -O3
mpi_flags = mpicc -std=c11 -O3

serial_program = functions.c count_friends_of_ten.c
mpi_program = functions.c mpi_count_friends_of_ten.c

serial = serial.x
mpi = parallel.x

all: ${serial} ${mpi}

${serial}: serial_main.c
	${serial_flags} ${serial_program} serial_main.c -o ${serial}	

${mpi}: mpi_main.c
	${mpi_flags} ${mpi_program} mpi_main.c -o ${mpi}

