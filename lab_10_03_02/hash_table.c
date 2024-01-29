#include "hash_table.h"
#include <string.h>
#include <stdlib.h>

static size_t hash_function(const char *key)
{
    unsigned int hash = 0;
    while (*key)
        hash = (hash << 5) + *key++;
    return hash % HASH_SIZE;
}

hash_table_t *hash_table_init(void)
{
    hash_table_t *table = malloc(sizeof(hash_table_t));
    if (!table)
        return NULL;
    for (size_t i = 0; i < HASH_SIZE; ++i)
        table->hash_map[i] = NULL;
    return table;
}

int hash_table_add(hash_table_t *hash_table, const char *key, int val)
{
    if (!hash_table)
        return ERR_PARAM;
    node_t *new_node = node_create(key, val);
    if (!new_node)
        return ERR_MEM;
    int rc = OK;
    
    size_t hash = hash_function(key);

    node_t *curr = hash_table->hash_map[hash];
    if (!curr)
    {
        hash_table->hash_map[hash] = new_node;
        return OK;
    }
    for (;!rc && curr->next != NULL; curr = curr->next)
        if (strcmp(curr->key, key) == 0)
            rc = ERR_EXISTS;
    
    if (!rc && strcmp(curr->key, key) != 0)
    {
        curr->next = new_node;
        new_node->prev = curr;
        return OK;
    }
    
    node_free(new_node);
    return ERR_EXISTS;
}

int hash_table_remove(hash_table_t *hash_table, const char *key)
{
    if (!hash_table)
        return ERR_PARAM;
    
    size_t hash = hash_function(key);

    node_t *curr = hash_table->hash_map[hash];
    if (!curr)
    {
        return ERR_NOT_FOUND;
    }
    for (; curr != NULL; curr = curr->next)
    {
        if (strcmp(curr->key, key) == 0)
        {
            if (curr->prev == NULL)
                hash_table->hash_map[hash] = curr->next;
            else
                curr->prev->next = curr->next;
            if (curr->next != NULL)
                curr->next->prev = curr->prev;

            node_free(curr);
            return OK;
        }
    }

    return ERR_NOT_FOUND;
}

int hash_table_find(hash_table_t *hash_table, const char *key, int **val)
{
    if (!hash_table)
        return ERR_PARAM;
    
    size_t hash = hash_function(key);

    node_t *curr = hash_table->hash_map[hash];
    if (!curr)
    {
        return ERR_NOT_FOUND;
    }
    for (; curr != NULL; curr = curr->next)
    {
        if (strcmp(curr->key, key) == 0)
        {
            *val = &curr->val;
            return OK;
        }
    }

    return ERR_NOT_FOUND;
}

int hash_table_find_min(hash_table_t *hash_table, int **val)
{
    if (!hash_table)
        return ERR_PARAM;

    const char *found = NULL;
    for (size_t i = 0; i < HASH_SIZE; ++i)
    {
        if (hash_table->hash_map[i])
        {
            for (node_t *curr = hash_table->hash_map[i]; curr != NULL; curr = curr->next)
            {
                if (found == NULL || strcmp(curr->key, found) < 0)
                {
                    *val = &curr->val;
                    found = curr->key;
                }
            }
        }
    }

    if (!found)
        return ERR_NOT_FOUND;
    return OK;
}

int hash_table_find_max(hash_table_t *hash_table, int **val)
{
    if (!hash_table)
        return ERR_PARAM;

    const char *found = NULL;
    for (size_t i = 0; i < HASH_SIZE; ++i)
    {
        if (hash_table->hash_map[i])
        {
            for (node_t *curr = hash_table->hash_map[i]; curr != NULL; curr = curr->next)
            {
                if (found == NULL || strcmp(curr->key, found) > 0)
                {
                    *val = &curr->val;
                    found = curr->key;
                }
            }
        }
    }

    if (!found)
        return ERR_NOT_FOUND;
    return OK;
}

bool hash_table_is_empt(hash_table_t *hash_table)
{
    for (size_t i = 0; i < HASH_SIZE; ++i)
        if (hash_table->hash_map[i])
            return false;

    return true;
}

void hash_table_make_empt(hash_table_t *hash_table)
{
    if (!hash_table)
        return;

    for (size_t i = 0; i < HASH_SIZE; ++i)
    {
        if (hash_table->hash_map[i])
        {
            node_t *curr = hash_table->hash_map[i];
            while (curr->next)
            {
                curr = curr->next;
                node_free(curr->prev);
            }
            node_free(curr);
            hash_table->hash_map[i] = NULL;
        }
    }
}

void hash_table_free(hash_table_t *hash_table)
{
    hash_table_make_empt(hash_table);
    free(hash_table);
}
