#include "associative_array_pair.h"
#include <stdlib.h>
#include <string.h>

pair_t *pair_create(const char *key, int val)
{
    pair_t *pair;
    pair = malloc(sizeof(pair_t));
    if (pair == NULL)
        return NULL;

    pair->key = key;
    pair->val = val;
    return pair;
}

void pair_free(void *p)
{
    pair_t *pair = p;
    free(pair);
}

int pair_cmp(const void *l, const void *r)
{
    const pair_t *l_pair = l, *r_pair = r;
    return strcmp(l_pair->key, r_pair->key);
}
