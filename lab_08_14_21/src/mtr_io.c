#include "mtr_io.h"
#include "mtr_alloc.h"
#include <math.h>

void matrix_fill_null(double **data, size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            data[i][j] = 0;
}

void matrix_fill_d_ones(double **data, size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            if (i == j)
                data[i][j] = 1;
            else
                data[i][j] = 0;
        }
    }
}

void matrix_copy(double **src, size_t n, size_t m, double **dest)
{
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            dest[i][j] = src[i][j];
}

int matrix_read_coord(FILE *f, double **data, size_t n, size_t m, size_t cnt_el)
{
    size_t n_curr_str, m_curr_row;
    double curr_el;

    for (size_t i = 0; i < cnt_el; ++i)
    {
        if (fscanf(f, "%lu %lu %lf\n", &n_curr_str, &m_curr_row, &curr_el) != 3)
            return ERR_IO;
        if (n_curr_str > n || m_curr_row > m)
            return ERR_RANGE;
        n_curr_str--;
        m_curr_row--;
        // Если либо в матрице элемент уже заполнен, либо считанный элемнт равен нулю
        if (fabs(data[n_curr_str][m_curr_row]) > EPS || fabs(curr_el) <= EPS)
            return ERR_IO;
        data[n_curr_str][m_curr_row] = curr_el;
    }
    if (!feof(f))
        return ERR_IO;
    return OK;
}

int matrix_create(FILE *f, double ***data, size_t *n, size_t *m)
{
    int rc;
    size_t cnt_el;

    if (fscanf(f, "%lu %lu %lu\n", n, m, &cnt_el) != 3)
        return ERR_IO;
    if (*n == 0 || *m == 0)
        return ERR_RANGE;

    *data = matrix_allocate(*n, *m);
    if (*data == NULL)
        return ERR_MEM;

    matrix_fill_null(*data, *n, *m);
    rc = matrix_read_coord(f, *data, *n, *m, cnt_el);
    if (rc)
    {
        matrix_free(*data, *n);
        return rc;
    }
    return OK;
}

void matrix_print_simple(FILE *f, double **data, size_t n, size_t m)
{
    fprintf(f, "%lu %lu\n", n, m);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            if (fabs(data[i][j]) <= EPS)
                fprintf(f, "%lf ", (float)0);
            else
                fprintf(f, "%lf ", data[i][j]);
        }
        fprintf(f, "\n");
    }
}
