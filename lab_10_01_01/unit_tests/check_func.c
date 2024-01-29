#include "check_func.h"
#include <string.h>

bool film_eq(struct film_t *l, struct film_t *r)
{
    return (strcmp(l->title, r->title) == 0) && (strcmp(l->name, r->name) == 0) && (l->year == r->year);
}

int film_arr_eq(struct film_t *l_arr, struct film_t *r_arr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        if (!film_eq(&l_arr[i], &r_arr[i]))
            return i;
    return ERR_OK;
}

void fa_print(FILE *f, const struct film_t *film_arr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        film_print(f, &film_arr[i]);
}

int film_arr_eq_list(struct film_t *arr, size_t n, node_t *head)
{
    size_t i = 0;
    for (node_t *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        if (!film_eq(tmp->data, &arr[i]))
            return i;
        i++;
    }
    if (i != n)
        return ERR_SIZE;
    return ERR_OK;
}

int init_list_from_int_arr(node_t **head, int *arr, size_t n)
{
    if (n == 0)
    {
        *head = NULL;
        return ERR_OK;
    }
    node_t *tmp;
    tmp = node_create(&arr[0]);
    if (!tmp)
        return ERR_MEM_UNIT;
    *head = tmp;
    for (size_t i = 1; i < n; ++i)
    {
        tmp = node_create(&arr[i]);
        if (!tmp)
        {
            list_free(*head);
            return ERR_MEM_UNIT;
        }
        *head = list_add_tail(*head, tmp);
    }
    return ERR_OK;
}

int int_arr_eq_list(int *arr, size_t n, node_t *head)
{
    size_t i = 0;
    for (node_t *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        if (*((int*)(tmp->data)) != arr[i])
            return i;
        i++;
    }
    if (i != n)
        return ERR_SIZE;
    return ERR_OK;
}

int read_int_arr(FILE *f, int *arr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        if (fscanf(f, "%d", &arr[i]) != 1)
            return ERR_SIZE;
    return ERR_OK;
}

void print_int(FILE* f, const void* num)
{
    const int *x = num;
    fprintf(f, "%d ", *x);
}

void print_double(FILE* f, const void* num)
{
    const double *x = num;
    fprintf(f, "%lf ", *x);
}

int cmp_int(const void *a, const void *b)
{
    return (*(const int*)a) - (*(const int*)b);
}
