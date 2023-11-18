#ifndef CHECK_FUNC_H
#define CHECK_FUNC_H

#include <stdio.h>
#include <stddef.h>

#define N_MAX 5
#define M_MAX 5

#define EPS 1e-7

void matrix_print_coord(FILE *f, double **data, size_t n, size_t m, size_t n_el);

int matrix_read_simple(FILE *f, double **data, size_t *n, size_t *m);

#endif
