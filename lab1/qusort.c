#include "qusort.h"

void qusort(int *left, int *right)
{
    int *l, *r;
    while (right - left >= 50)
    {
        partition(left, right, &l, &r, &left, &right);
        qusort(l, r);
    }
    insert_sort(left, right);
}

void sort(int *data, int len)
{
    qusort(data, data + len - 1);
}

int main(int argc, char *argv[])
{
    int size = SIZE;
    if (argc == 2)
    {
        size = atoi(argv[1]);
    }
    init(&data, size);
    printf("Sorting %d numbers with Single Thread Quicksort ...\n",
           size);
    t();
    sort(data, size);
    printf("%.6fs\n", t());
    test(data, size);
    free(data);
    return 0;
}