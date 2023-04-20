#include <mpi.h>
#include <iostream>
#include <random>
#include <cmath>

double f(double x1, double x2, double x3) {
    return exp(-(x1*x1 + x2*x2 + x3*x3));
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();

    const double a = -1.0;
    const double b = 1.0;
    const int n = 1000000000; // number of samples per process
    const double m = 1e-5; // absolute error tolerance
    const double v = pow((b-a), 3); // volume of the integration domain
    double sum = 0.0;
    double local_sum = 0.0;

    int N_proc = n / size;

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd() + rank);
    std::uniform_real_distribution<double> dis(a, b);

    // compute local sum
    for (int i = 0; i < N_proc; i++) {
        double x1 = dis(gen);
        double x2 = dis(gen);
        double x3 = dis(gen);
        local_sum += f(x1, x2, x3);
    }

    // compute global sum using MPI_Reduce
    MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();
    double elapsed_time = end_time - start_time;


    // compute integral estimate and error
    double integral = sum / (n) * v;
    double error = fabs(integral - 3.33230708709311); // exact value of the integral

    if (rank == 0) {
        std::cout << "Integral estimate: " << integral << std::endl;
        std::cout << "Error estimate: " << error << std::endl;
	std::cout << "Elapsed time: " << elapsed_time << " seconds"  << std::endl;
    }

    MPI_Finalize();

    return 0;
}
