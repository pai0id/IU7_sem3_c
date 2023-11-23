#ifndef CHECK_FUNC_H
#define CHECK_FUNC_H

#include <stdio.h>
#include <stddef.h>

#define N_MAX 5
#define M_MAX 5

#define EPS 1e-7

#define ERR_OK 0
#define ERR_DIFF_EL 1
#define ERR_DIFF_SIZE 2

void matrix_print_coord(FILE *f, double **data, size_t n, size_t m, size_t n_el);

int matrix_read_simple(FILE *f, double **data, size_t *n, size_t *m);

int double_mtr_eq(double **l_mtr, size_t l_n, size_t l_m, double **r_mtr, size_t r_n, size_t r_m);

int double_arr_eq(double *l_arr, size_t l_n, double *r_arr, size_t r_n);

#endif
