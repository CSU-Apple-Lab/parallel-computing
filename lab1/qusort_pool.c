#include "qusort.h"
#include <pthread.h>
#include <unistd.h>

typedef struct
{
    int *left;
    int *right;
} Task;

typedef struct
{
    int thread_num;
    pthread_t *threads;
    Task *tasks;
    int task_count;
    int quit;
    pthread_mutex_t mutex;
    pthread_cond_t task_cond;
    pthread_cond_t exit_cond;
} ThreadPool;

ThreadPool global_pool;

void add_task(ThreadPool *pool, Task task)
{
    pthread_mutex_lock(&(pool->mutex));

    while (pool->task_count >= pool->thread_num)
    {
        pthread_cond_wait(&(pool->task_cond), &(pool->mutex));
    }

    pool->tasks[pool->task_count++] = task;
    pthread_cond_signal(&(pool->task_cond));
    pthread_mutex_unlock(&(pool->mutex));
}

void qusort(int *left, int *right)
{
    while (right - left >= 50)
    {
        int *l, *r;
        partition(left, right, &l, &r, &left, &right);

        if (right - left > 100000)
        {
            Task task1 = {left, right};
            add_task(&global_pool, task1);
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

void *sort_thr(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;

    while (1)
    {
        pthread_mutex_lock(&(pool->mutex));

        while (pool->task_count <= 0 && !pool->quit)
        {
            pthread_cond_wait(&(pool->task_cond), &(pool->mutex));
        }

        if (pool->quit)
        {
            pthread_mutex_unlock(&(pool->mutex));
            pthread_exit(NULL);
        }

        Task task = pool->tasks[--pool->task_count];
        pthread_mutex_unlock(&(pool->mutex));

        qusort(task.left, task.right);

        pthread_mutex_lock(&(pool->mutex));
        if (!pool->task_count)
        {
            pthread_cond_signal(&(pool->exit_cond));
            pthread_mutex_unlock(&(pool->mutex));
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&(pool->mutex));
    }

    return NULL;
}

void destroy_pool(ThreadPool *pool)
{
    pthread_mutex_lock(&(pool->mutex));
    while (pool->task_count)
    {
        pthread_cond_wait(&(pool->exit_cond), &(pool->mutex));
    }

    pool->quit = 1;
    pthread_cond_broadcast(&(pool->task_cond));
    pthread_mutex_unlock(&(pool->mutex));

    for (int i = 0; i < pool->thread_num; i++)
    {
        pthread_join(pool->threads[i], NULL);
    }

    free(pool->threads);
    free(pool->tasks);
    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->task_cond));
    pthread_cond_destroy(&(pool->exit_cond));
}

void init_pool(ThreadPool *pool, int thread_num)
{
    pool->thread_num = thread_num;
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_num);
    pool->tasks = (Task *)malloc(sizeof(Task) * thread_num);
    pool->task_count = 0;
    pool->quit = 0;
    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->task_cond), NULL);
    pthread_cond_init(&(pool->exit_cond), NULL);

    for (int i = 0; i < thread_num; i++)
    {
        pthread_create(&(pool->threads[i]), NULL, sort_thr, (void *)pool);
    }
}

void sort(int *data, int len)
{
    int max_threads;
    int n_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (n_cpus > 0)
        max_threads = n_cpus * 2;
    else
        max_threads = 8;
    init_pool(&global_pool, max_threads);
    Task task = {data, data + len - 1};
    add_task(&global_pool, task);
    destroy_pool(&global_pool);
}

int main(int argc, char *argv[])
{
    int size = SIZE;
    if (argc == 2)
    {
        size = atoi(argv[1]);
    }
    init(&data, size);
    printf("Sorting %d numbers with Thread Pool Quicksort ...\n",
           size);
    t();
    sort(data, size);
    printf("%.6fs\n", t());
    // test(data, size);
    return 0;
}