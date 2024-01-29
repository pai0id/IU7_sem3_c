#include "list.h"

node_t *list_add_tail(node_t *head, node_t *pnode)
{
    if (!head)
        return pnode;
    node_t *tmp;
    for (tmp = head; tmp->next != NULL; tmp = tmp->next) ;
    tmp->next = pnode;
    return head;
}

void list_print(FILE *f, node_t *head, void (*print)(FILE*, const void*))
{
    for (node_t *tmp = head; tmp != NULL; tmp = tmp->next)
        node_print(f, tmp, print);
}

void list_free(node_t *head)
{
    node_t *next;
    for (node_t *curr = head; curr != NULL;)
    {
        next = curr->next;
        node_free(curr);
        curr = next;
    }
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*))
{
    node_t *res = NULL;
    for (node_t *curr = head; curr != NULL; curr = curr->next)
        if (comparator(curr->data, data) == 0)
            res = curr;
    return res;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (*head == before)
    {
        elem->next = *head;
        *head = elem;
    }
    else
    {
        for (node_t *curr = *head; curr != NULL; curr = curr->next)
        {
            if (curr->next == before)
            {
                elem->next = curr->next;
                curr->next = elem;
                curr = elem;
            }
        }
    }
}

void remove_duplicates(node_t **head, int (*comparator)(const void*, const void*))
{
    node_t *tmp;
    for (node_t *curr = *head; curr != NULL; curr = curr->next)
    {
        while (curr->next && comparator(curr->data, curr->next->data) == 0)
        {
            tmp = curr->next;
            curr->next = curr->next->next;
            node_free(tmp);
        }
    }
}

void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL || head->next == NULL)
    {
        *back = NULL;
        return;
    }

    node_t *slow = head;
    node_t *fast = head->next;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    *back = slow->next;
    slow->next = NULL;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void*, const void*))
{
    node_t *merged_head = NULL;
    node_t *current = NULL;

    if (*head_a == NULL)
        merged_head = *head_b;
    if (*head_b == NULL)
        merged_head = *head_a;

    while (*head_a && *head_b)
    {
        if (comparator((*head_a)->data, (*head_b)->data) <= 0)
        {
            if (merged_head == NULL)
            {
                merged_head = *head_a;
                current = merged_head;
            }
            else
            {
                current->next = *head_a;
                current = current->next;
            }
            *head_a = (*head_a)->next;
        }
        else
        {
            if (merged_head == NULL)
            {
                merged_head = *head_b;
                current = merged_head;
            }
            else
            {
                current->next = *head_b;
                current = current->next;
            }
            *head_b = (*head_b)->next;
        }
    }

    if (current && *head_a)
        current->next = *head_a;
    else if (current && *head_b)
        current->next = *head_b;

    *head_a = NULL;
    *head_b = NULL;

    return merged_head;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (head == NULL || head->next == NULL)
        return head;

    node_t *front = head;
    node_t *back;

    front_back_split(front, &back);

    front = sort(front, comparator);
    back = sort(back, comparator);

    return sorted_merge(&front, &back, comparator);
}
