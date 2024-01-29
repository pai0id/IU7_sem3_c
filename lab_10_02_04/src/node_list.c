#include "node_list.h"
#include <stdlib.h>

node_t *node_create(int num, int pow)
{
    node_t *node;
    node = malloc(sizeof(node_t));
    if (node == NULL)
        return NULL;
    node->num = num;
    node->pow = pow;
    node->next = NULL;
    return node;
}

void node_free(node_t *node)
{
    free(node);
}

void node_print(FILE *f, const node_t *node)
{
    fprintf(f, "%d %d ", node->num, node->pow);
}
