#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "associative_array_pair.h"
#include "associative_array.h"

struct assoc_array_type
{
    list_t *list;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (!arr)
        return NULL;
    arr->list = list_init();
    if (!arr->list)
    {
        free(arr);
        return NULL;
    }
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr && *arr)
    {
        assoc_array_clear(*arr);
        list_free((*arr)->list, pair_free);
        free(*arr);
        *arr = NULL;
    }
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !key || key[0] == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    pair_t *pair = pair_create(key, num);
    if (!pair)
        return ASSOC_ARRAY_MEM;

    if (list_find(arr->list, pair, pair_cmp))
    {
        pair_free(pair);
        return ASSOC_ARRAY_KEY_EXISTS;
    }

    list_t *tmp = list_add_tail(arr->list, pair);
    if (tmp)
    {
        arr->list = tmp;
        return ASSOC_ARRAY_OK;
    }
    else
    {
        pair_free(pair);
        return ASSOC_ARRAY_MEM;
    }
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || key[0] == 0 || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    pair_t *pair = pair_create(key, 0);
    if (!pair)
        return ASSOC_ARRAY_MEM;

    node_t *node = list_find(arr->list, pair, pair_cmp);
    pair_free(pair);

    if (!node)
        return ASSOC_ARRAY_NOT_FOUND;
    *num = &((pair_t *)(node->data))->val;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || key[0] == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    pair_t *pair = pair_create(key, 0);
    if (!pair)
        return ASSOC_ARRAY_MEM;

    if (!list_find(arr->list, pair, pair_cmp))
    {
        pair_free(pair);
        return ASSOC_ARRAY_NOT_FOUND;
    }

    arr->list = list_remove(arr->list, pair, pair_cmp, pair_free);
    pair_free(pair);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    list_make_empt(arr->list, pair_free);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->list->head;
    while (current)
    {
        action(((pair_t *)(current->data))->key, &((pair_t *)(current->data))->val, param);
        current = current->next;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (list_is_empt(arr->list))
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *node = list_find_min(arr->list, pair_cmp);
    *num = &((pair_t *)(node->data))->val;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (list_is_empt(arr->list))
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *node = list_find_max(arr->list, pair_cmp);
    *num = &((pair_t *)(node->data))->val;

    return ASSOC_ARRAY_OK;
}
