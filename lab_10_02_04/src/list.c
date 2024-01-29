#include "list.h"
#include <math.h>

node_t *list_add_tail(node_t *head, node_t *pnode)
{
    if (!head)
        return pnode;
    node_t *tmp;
    for (tmp = head; tmp->next != NULL; tmp = tmp->next) ;
    tmp->next = pnode;
    return head;
}

int init_list_from_num(node_t **head, int num)
{
    *head = NULL;  // Инициализация головы списка.

    node_t *tmp;  // Временный указатель на узел списка.
    int sqrt_num = (int)sqrt(num) + 1;  // Корень из числа num + 1 для оптимизации проверки делителей.
    int probe;

    // Перебор всех возможных делителей от 2 до sqrt(num).
    // Перебор ведется до квадратного корня числа (sqr) из-за математического свойства простых чисел.
    // Если число не является простым и имеет делители, то как минимум один из них будет меньше или равен квадратному корню из этого числа.
    for (probe = 2; probe <= sqrt_num; ++probe)
    {
        int pow = 0;

        // Пока число делится на текущий делитель, увеличиваем степень и уменьшаем число.
        while (num % probe == 0)
        {
            pow++;
            num /= probe;
        }

        // Если степень больше нуля, создаем новый узел и добавляем его в конец списка.
        if (pow > 0)
        {
            tmp = node_create(probe, pow);
            // Проверка на успешное выделение памяти для нового узла.
            if (!tmp)
            {
                list_free(*head);
                return ERR_MEM;
            }
            // Добавляем узел в конец списка.
            *head = list_add_tail(*head, tmp);
        }
    }

    // Если после перебора делителей осталось число больше 1, добавляем его в список с степенью 1.
    if (num > 1)
    {
        tmp = node_create(num, 1);
        if (!tmp)
        {
            list_free(*head);
            return ERR_MEM;
        }
        *head = list_add_tail(*head, tmp);
    }
    return OK;
}

int get_num_from_list(node_t *head)
{
    int num = 1;
    for (node_t *curr = head; curr != NULL; curr = curr->next)
        num *= (int)pow(curr->num, curr->pow);
    return num;
}

void print_factor(FILE *f, const void *num)
{
    const node_t *node = num;
    fprintf(f, "%d %d ", node->num, node->pow);
}

void print_num(FILE *f, node_t *head)
{
    list_print_reverse(f, head, print_factor);
    fprintf(f, "1\n");
}

void list_print_reverse(FILE *f, node_t *head, void (*print)(FILE*, const void*))
{
    if (head != NULL)
    {
        list_print_reverse(f, head->next, print);
        print(f, head);
    }
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
