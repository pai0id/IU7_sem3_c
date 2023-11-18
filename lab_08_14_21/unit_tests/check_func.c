#include "check_func.h"
#include <math.h>
#include <check.h>
#include "err.h"

/// Печать матрицы в координатном виде
void matrix_print_coord(FILE *f, double **data, size_t n, size_t m, size_t n_el)
{
    fprintf(f, "%lu %lu %lu\n", n, m, n_el);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (fabs(data[i][j]) >= EPS)
                fprintf(f, "%lu %lu %lf\n", i + 1, j + 1, data[i][j]);
}

/// Чтение матрицы в простом виде
int matrix_read_simple(FILE *f, double **data, size_t *n, size_t *m)
{
    if (fscanf(f, "%lu %lu\n", n, m) != 2)
        return ERR_IO;
    for (size_t i = 0; i < *n; ++i)
        for (size_t j = 0; j < *m; ++j)
            if (fscanf(f, "%lf", &(data[i][j])) != 1)
                return ERR_IO;
    return OK;
}
