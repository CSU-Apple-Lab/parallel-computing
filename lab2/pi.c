#include "pi.h"
#include <time.h>

int main(int argc, char *argv[])
{
    double pi = 0.0, sum = 0.0, cost_time = 0.0;

    // Get the begin time
    cost_time -= clock();

    // Caculate PI
    sum = cal_thread_sum(0, 1);
    pi = 4 * dmt * sum;

    // Get the cost time
    cost_time += clock();
    cost_time /= CLOCKS_PER_SEC;
    printf("Np=1\t\tTime=%lfs\t\tPI=%.8lf\n", cost_time, pi);

    return cost_time;
}