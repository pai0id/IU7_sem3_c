#ifndef ASSOC_ARR_PAIR_H
#define ASSOC_ARR_PAIR_H

typedef struct
{
    const char *key;
    int val;
} pair_t;

pair_t *pair_create(const char *key, int val);

void pair_free(void *p);

int pair_cmp(const void *l_pair, const void *r_pair);

#endif
