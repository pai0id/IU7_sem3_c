#ifndef CHECK_FUNC_H
#define CHECK_FUNC_H

#include "film.h"
#include "film_arr.h"
#include "list.h"
#include <stdio.h>
#include <stdbool.h>

#define N_MAX 10

#define ERR_OK -1
#define ERR_SIZE -2
#define ERR_MEM_UNIT -3

bool film_eq(struct film_t *l, struct film_t *r);

int film_arr_eq(struct film_t *l_arr, struct film_t *r_arr, size_t n);

void fa_print(FILE *f, const struct film_t *film_arr, size_t n);

int film_arr_eq_list(struct film_t *arr, size_t n, node_t *head);


int init_list_from_int_arr(node_t **head, int *arr, size_t n);

int int_arr_eq_list(int *arr, size_t n, node_t *head);

int read_int_arr(FILE *f, int *arr, size_t n);

void print_int(FILE* f, const void* num);

void print_double(FILE* f, const void* num);

int cmp_int(const void *a, const void *b);

#endif
