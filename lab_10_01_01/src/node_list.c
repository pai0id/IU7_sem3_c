#include "node_list.h"
#include <stdlib.h>

node_t *node_create(void *data)
{
    node_t *node;
    node = malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

void node_free(node_t *node)
{
    free(node);
}

void node_print(FILE *f, const node_t *node, void (*print)(FILE*, const void*))
{
    print(f, node->data);
}
