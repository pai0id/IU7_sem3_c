#ifndef CHECK_FUNC_H
#define CHECK_FUNC_H

#include "list.h"
#include <stdio.h>

#define N_MAX 10
#define FACT_CHARS 2

#define ERR_OK -1
#define ERR_SIZE -2

int fact_arr_eq_list(int arr[][FACT_CHARS], size_t n, node_t *head);

int read_int_arr(FILE *f, int *arr, size_t n);

int int_arr_eq(int *l_arr, int *r_arr, size_t n);

#endif
