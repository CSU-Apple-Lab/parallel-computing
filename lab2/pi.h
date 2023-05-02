#include <stdio.h>

#define N 1E8
#define dmt 1E-8
#define dmt_sqr 1E-16

// calculates pi in one thread, return cost time
double pi();

// calculates pi using MPI, return cost time
double pi_mpi();

// cal_thread_sum calculates sun of each thread, in which np means step
double cal_thread_sum(int rank, int np)
{
    double sum_th = 0.0;
    for (int i = rank; i < N; i += np)
    {
        sum_th += 1.0 / (1.0 + dmt_sqr * i * i);
    }
    return sum_th;
}
