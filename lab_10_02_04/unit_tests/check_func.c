#include "check_func.h"

int fact_arr_eq_list(int arr[][FACT_CHARS], size_t n, node_t *head)
{
    size_t i = 0;
    for (node_t *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->num != arr[i][0] || tmp->pow != arr[i][1])
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

int int_arr_eq(int *l_arr, int *r_arr, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        if (l_arr[i] != r_arr[i])
            return i;
    return ERR_OK;
}
