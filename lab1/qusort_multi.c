#include "qusort.h"
#include <pthread.h>
#include <unistd.h>

int max_threads;
int n_threads;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *sort_thr(void *arg)
{
    int **par = (int **)arg;
    qusort(par[0], par[1]);
    free(arg);
    pthread_mutex_lock(&mutex);
    n_threads -= 1;
    if (n_threads == 0)
        pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void qusort(int *left, int *right)
{
    while (right - left >= 50)
    {
        int *l, *r;
        partition(left, right, &l, &r, &left, &right);

        if (right - left > 100000 && n_threads < max_threads)
        {
            // start a new thread - max_threads is a soft limit
            pthread_t thread;
            int **param = malloc(2 * sizeof(int *));
            param[0] = left;
            param[1] = right;
            pthread_mutex_lock(&mutex);
            n_threads += 1;
            pthread_mutex_unlock(&mutex);
            pthread_create(&thread, NULL, sort_thr, param);
            left = l;
            right = r;
        }
        else
        {
            qusort(l, r);
        }
    }
    insert_sort(left, right);
}

void sort(int *data, int len)
{
    int n_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (n_cpus > 0)
        max_threads = n_cpus * 2;
    else
        max_threads = 8;

    pthread_t thread;
    int **param = malloc(2 * sizeof(int *));
    param[0] = data;
    param[1] = data + len - 1;
    n_threads = 1;
    pthread_create(&thread, NULL, sort_thr, param);

    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
    int size = SIZE;
    if (argc == 2)
    {
        size = atoi(argv[1]);
    }
    init(&data, size);
    printf("Sorting %d numbers with Multi Thread Quicksort ...\n",
           size);
    t();
    sort(data, size);
    printf("%.6fs\n", t());
    test(data, size);
    free(data);
    return 0;
}