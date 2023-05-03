#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define SIZE (50 * 1000000)

int *data;

#define swap(a, b)  \
    {               \
        int _h = a; \
        a = b;      \
        b = _h;     \
    }

#define min(a, b) ((a) < (b) ? (a) : (b))

#define sort3fast(a, b, c)  \
    if (b < a)              \
    {                       \
        if (c < a)          \
        {                   \
            if (c < b)      \
            {               \
                swap(a, c); \
            }               \
            else            \
            {               \
                int h = a;  \
                a = b;      \
                b = c;      \
                c = h;      \
            }               \
        }                   \
        else                \
        {                   \
            swap(a, b);     \
        }                   \
    }                       \
    else                    \
    {                       \
        if (c < b)          \
        {                   \
            if (c < a)      \
            {               \
                int h = c;  \
                c = b;      \
                b = a;      \
                a = h;      \
            }               \
            else            \
            {               \
                swap(b, c); \
            }               \
        }                   \
    }

void qusort(int *left, int *right);

void init(int **data, int len)
{
    *data = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++)
    {
        (*data)[i] = rand();
    }
}

double t(void)
{
    static double t0;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double h = t0;
    t0 = tv.tv_sec + tv.tv_usec / 1000000.0;
    return t0 - h;
}

void print(int *data, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", data[i]);
    }
}

void test(int *data, int len)
{
    for (int i = 1; i < len; i++)
    {
        if (data[i] < data[i - 1])
        {
            printf("idx:{%d, %d}, val:{%d, %d}\n", i - 1, i, data[i - 1], data[i]);
            printf("ERROR\n");
            break;
        }
    }
}

void insert_sort(int *left, int *right)
{
    // put minimum to left position, so we can save
    // one inner loop comparsion for insert sort
    for (int *pi = left + 1; pi <= right; pi++)
    {
        if (*pi < *left)
        {
            swap(*pi, *left);
        }
    }
    for (int *pi = left + 2; pi <= right; pi++)
    {
        int h = *pi;
        int *pj = pi - 1;
        while (h < *pj)
        {
            *(pj + 1) = *pj;
            pj -= 1;
        }
        *(pj + 1) = h;
    }
}

void partition(int *left0, int *right0, int **l1, int **r1, int **l2, int **r2)
{
    int *left = left0 + 1;
    int *right = right0;

    int *mid = left0 + (right0 - left0) / 2;
    int piv = *mid;
    *mid = *left;
    sort3fast(*left0, piv, *right0);
    *left = piv;

    while (1)
    {
        do
            left += 1;
        while (*left < piv);
        do
            right -= 1;
        while (*right > piv);
        if (left >= right)
            break;
        swap(*left, *right);
    }
    *(left0 + 1) = *right;
    *right = piv;

    if (right < mid)
    {
        *l1 = left0;
        *r1 = right - 1;
        *l2 = right + 1;
        *r2 = right0;
    }
    else
    {
        *l1 = right + 1;
        *r1 = right0;
        *l2 = left0;
        *r2 = right - 1;
    }
}
