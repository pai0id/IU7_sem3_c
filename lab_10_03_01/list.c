#include "list.h"
#include <stdlib.h>

list_t *list_init(void)
{
    list_t *list = malloc(sizeof(list_t));
    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

list_t *list_add_tail(list_t *list, const void *data)
{
    if (!list)
        return NULL;
    node_t *new_node = node_create((void *)data);
    if (!new_node)
        return NULL;
    if (list_is_empt(list))
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    return list;
}

list_t *list_remove(list_t *list, const void *data, int (*comparator)(const void*, const void*), void (*free_data)(void*))
{
    node_t *curr = list->head, *next;
    while (curr != NULL)
    {
        next = curr->next;
        if (comparator(curr->data, data) == 0)
        {
            if (curr->prev)
                curr->prev->next = curr->next;
            else
                list->head = curr->next;  // curr - голова
            
            if (curr->next)
                curr->next->prev = curr->prev;
            else
                list->tail = curr->prev;  // curr - хвост
            
            node_free(curr, free_data);
        }
        curr = next;
    }
    return list;
}

node_t *list_find(list_t *list, const void *data, int (*comparator)(const void*, const void*))
{
    node_t *res = NULL;
    for (node_t *curr = list->head; !res && curr != NULL; curr = curr->next)
        if (comparator(curr->data, data) == 0)
            res = curr;
    return res;
}

node_t *list_find_min(list_t *list, int (*comparator)(const void*, const void*))
{
    node_t *res = list->head;
    for (node_t *curr = res->next; curr != NULL; curr = curr->next)
        if (comparator(curr->data, res->data) < 0)
            res = curr;
    return res;
}

node_t *list_find_max(list_t *list, int (*comparator)(const void*, const void*))
{
    node_t *res = list->head;
    for (node_t *curr = res->next; curr != NULL; curr = curr->next)
        if (comparator(curr->data, res->data) > 0)
            res = curr;
    return res;
}

bool list_is_empt(list_t *list)
{
    return !list || !list->head || !list->tail;
}

void list_print(FILE *f, list_t *list, void (*print)(FILE*, const void*))
{
    for (node_t *tmp = list->head; tmp != NULL; tmp = tmp->next)
        node_print(f, tmp, print);
}

void list_make_empt(list_t *list, void (*free_data)(void*))
{
    node_t *next;
    for (node_t *curr = list->head; curr != NULL;)
    {
        next = curr->next;
        node_free(curr, free_data);
        curr = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

void list_free(list_t *list, void (*free_data)(void*))
{
    list_make_empt(list, free_data);
    free(list);
}
