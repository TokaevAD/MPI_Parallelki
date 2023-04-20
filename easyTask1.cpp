#include <stdio.h>
#include "mpi.h"
#include <cmath>
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{
	int proc_number, proc_count, message;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_number);


	if (proc_number == 0) {
		printf("Process %i from %i processes\n", proc_number, proc_count);
		/*for (int i = 1; i < proc_count; i++) {
			MPI_Recv(&message, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		}*/
	}
	else {
		//MPI_Send(&proc_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		printf("Process %i from %i processes\n", proc_number, proc_count);
	}

	MPI_Finalize();
	return 0;
}




