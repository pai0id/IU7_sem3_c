#ifndef NODE_HASK_TABLE_H
#define NODE_HASK_TABLE_H

#include <stdio.h>

typedef struct node_t
{
    const char *key;
    int val;
    struct node_t *next;
    struct node_t *prev;
} node_t;

node_t *node_create(const char *key, int val);

void node_free(node_t *node);

#endif
