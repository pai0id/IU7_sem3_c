#include "task_funcs.h"

int init_list_from_film_arr(node_t **head, struct film_t *film_arr, size_t n_films)
{
    if (n_films == 0)
    {
        *head = NULL;
        return OK;
    }
    node_t *tmp;
    tmp = node_create(&film_arr[0]);
    if (!tmp)
        return ERR_MEM;
    *head = tmp;
    for (size_t i = 1; i < n_films; ++i)
    {
        tmp = node_create(&film_arr[i]);
        if (!tmp)
        {
            list_free(*head);
            return ERR_MEM;
        }
        *head = list_add_tail(*head, tmp);
    }
    return OK;
}
