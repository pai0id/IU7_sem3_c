#ifndef HASK_TABLE_H
#define HASK_TABLE_H

#include "node_hash_table.h"
#include "stdbool.h"
#include "err.h"

#define HASH_SIZE 1000

typedef struct
{
    node_t *hash_map[HASH_SIZE];
} hash_table_t;

hash_table_t *hash_table_init(void);

int hash_table_add(hash_table_t *hash_table, const char *key, int val);

int hash_table_remove(hash_table_t *hash_table, const char *key);

int hash_table_find(hash_table_t *hash_table, const char *key, int **val);

int hash_table_find_min(hash_table_t *hash_table, int **val);

int hash_table_find_max(hash_table_t *hash_table, int **val);

bool hash_table_is_empt(hash_table_t *hash_table);

void hash_table_make_empt(hash_table_t *hash_table);

void hash_table_free(hash_table_t *hash_table);

#endif
