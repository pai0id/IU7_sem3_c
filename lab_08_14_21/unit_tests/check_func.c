#include "check_func.h"
#include "err.h"
#include <math.h>
#include <check.h>

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

int double_mtr_eq(double **l_mtr, size_t l_n, size_t l_m, double **r_mtr, size_t r_n, size_t r_m)
{
    if (l_n != r_n || l_m != r_m)
        return ERR_DIFF_SIZE;
    for (size_t i = 0; i < l_n; ++i)
        for (size_t j = 0; j < l_m; ++j)
            if (fabs(l_mtr[i][j] - r_mtr[i][j]) > EPS)
                return ERR_DIFF_EL;
    return ERR_OK;
}

int double_arr_eq(double *l_arr, size_t l_n, double *r_arr, size_t r_n)
{
    if (l_n != r_n)
        return ERR_DIFF_SIZE;
    for (size_t i = 0; i < l_n; ++i)
        if (fabs(l_arr[i] - r_arr[i]) > EPS)
            return ERR_DIFF_EL;
    return ERR_OK;
}
