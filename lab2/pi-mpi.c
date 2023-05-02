#include "pi.h"
#include <mpi.h>

#define ROOT 0

int main(int argc, char *argv[])
{
    int rank, np;
    double pi = 0.0, sum_th = 0.0, sum = 0.0, cost_time = 0.0;

    MPI_Init(NULL, NULL);

    // Get thread ID
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Master get thread Number
    if (ROOT == rank)
    {
        MPI_Comm_size(MPI_COMM_WORLD, &np);
    }
    // Master broadcast np to all thread
    MPI_Bcast(&np, 1, MPI_INT, ROOT, MPI_COMM_WORLD);

    // Synchronize all thread
    MPI_Barrier(MPI_COMM_WORLD);
    // Master get the begin time
    if (ROOT == rank)
    {
        cost_time -= MPI_Wtime();
    }

    // Each thread will caculate a part of the sum
    sum_th = cal_thread_sum(rank, np);

    // Sum up all thread sum
    MPI_Reduce(&sum_th, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Synchronize all thread
    MPI_Barrier(MPI_COMM_WORLD);
    // Master caculate PI and get the cost time
    if (ROOT == rank)
    {
        pi = 4 * dmt * sum;

        cost_time += MPI_Wtime();
        printf("Np=%d\t\tTime=%lfs\t\tPI=%.8lf\n", np, cost_time, pi);
    }

    MPI_Finalize();

    return cost_time;
}