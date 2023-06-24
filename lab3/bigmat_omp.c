#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

int NP = 1;
int A[N][N], B[N][N];

void matrixMultiply()
{
    int C[N][N];
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void init()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        NP = atoi(argv[1]);
    }

    init();
    omp_set_num_threads(NP);

    double elapsedTime;
    elapsedTime -= omp_get_wtime();
    matrixMultiply();
    elapsedTime += omp_get_wtime();
    printf("%.6lfs\n", elapsedTime);

    return 0;
}
