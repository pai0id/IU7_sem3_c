#include "node_hash_table.h"
#include <stdlib.h>

node_t *node_create(const char *key, int val)
{
    node_t *node;
    node = malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->key = key;
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void node_free(node_t *node)
{
    free(node);
}
