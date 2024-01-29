#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "associative_array.h"

struct assoc_array_type
{
    hash_table_t *hash_table;
};

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (!arr)
        return NULL;
    arr->hash_table = hash_table_init();
    if (!arr->hash_table)
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
        hash_table_free((*arr)->hash_table);
        free(*arr);
        *arr = NULL;
    }
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!arr || !key || key[0] == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    int rc = hash_table_add(arr->hash_table, key, num);

    switch (rc)
    {
        case ERR_MEM:
            return ASSOC_ARRAY_MEM;
        case ERR_EXISTS:
            return ASSOC_ARRAY_KEY_EXISTS;
        case ERR_PARAM:
            return ASSOC_ARRAY_INVALID_PARAM;
        case OK:
            return ASSOC_ARRAY_OK;
        default:
            return ASSOC_ARRAY_OK;
    }
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!arr || !key || key[0] == 0 || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    int rc = hash_table_find(arr->hash_table, key, num);

    switch (rc)
    {
        case ERR_NOT_FOUND:
            return ASSOC_ARRAY_NOT_FOUND;
        case ERR_PARAM:
            return ASSOC_ARRAY_INVALID_PARAM;
        case OK:
            return ASSOC_ARRAY_OK;
        default:
            return ASSOC_ARRAY_OK;
    }
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!arr || !key || key[0] == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    int rc = hash_table_remove(arr->hash_table, key);

    switch (rc)
    {
        case ERR_NOT_FOUND:
            return ASSOC_ARRAY_NOT_FOUND;
        case ERR_PARAM:
            return ASSOC_ARRAY_INVALID_PARAM;
        case OK:
            return ASSOC_ARRAY_OK;
        default:
            return ASSOC_ARRAY_OK;
    }
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    hash_table_make_empt(arr->hash_table);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < HASH_SIZE; ++i)
        if (arr->hash_table->hash_map[i])
            for (node_t *curr = arr->hash_table->hash_map[i]; curr != NULL; curr = curr->next)
                action(curr->key, &curr->val, param);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    int rc = hash_table_find_min(arr->hash_table, num);

    switch (rc)
    {
        case ERR_NOT_FOUND:
            return ASSOC_ARRAY_NOT_FOUND;
        case ERR_PARAM:
            return ASSOC_ARRAY_INVALID_PARAM;
        case OK:
            return ASSOC_ARRAY_OK;
        default:
            return ASSOC_ARRAY_OK;
    }
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    int rc = hash_table_find_max(arr->hash_table, num);

    switch (rc)
    {
        case ERR_NOT_FOUND:
            return ASSOC_ARRAY_NOT_FOUND;
        case ERR_PARAM:
            return ASSOC_ARRAY_INVALID_PARAM;
        case OK:
            return ASSOC_ARRAY_OK;
        default:
            return ASSOC_ARRAY_OK;
    }
}
