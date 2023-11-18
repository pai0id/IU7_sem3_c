#include "mtr_alloc.h"
#include <stdlib.h>

// void matrix_free(double **data, size_t n)
// {
//     double *min = data[0];
//     for (size_t i = 1; i < n; ++i)
//         if (data[i] < min)
//             min = data[i];
//     free(min);
//     free(data);
// }

// void matrix_free(double **data, size_t n)
// {
//     free(data[n]);
//     free(data);
// }

// double **matrix_allocate(size_t n, size_t m)
// {
//     double **ptrs, *data;
//     ptrs = malloc((n + 1) * sizeof(double*));
//     if (!ptrs)
//         return NULL;
//     data = malloc(n * m * sizeof(double));
//     if (!data)
//     {
//         free(ptrs);
//         return NULL;
//     }
//     ptrs[n] = data;
//     for (size_t i = 0; i < n; i++)
//         ptrs[i] = data + i * m;
//     return ptrs;
// }

void matrix_free(double **data, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        free(data[i]);
    free(data);
}

double **matrix_allocate(size_t n, size_t m)
{
    double **ptrs = calloc(n, sizeof(double *));
    if (ptrs == NULL)
        return NULL;
    for (size_t i = 0; i < n; i++)
    {
        ptrs[i] = malloc(m * sizeof(double));
        if (!ptrs[i])
        {
            matrix_free(ptrs, n);
            return NULL;
        }
    }
    return ptrs;
}
