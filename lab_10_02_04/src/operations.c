#include "operations.h"

node_t *mul_nums(node_t *num1, node_t *num2)
{
    // Инициализация результирующего списка и временного указателя
    node_t *res = NULL;
    node_t *tmp = NULL;

    // Итерация по обоим спискам до тех пор, пока один из них не закончится
    while (num1 && num2)
    {
        // Сравнение текущих множителей
        if (num1->num < num2->num)
        {
            // Создание нового узла с множителем и степенью из num1
            tmp = node_create(num1->num, num1->pow);
            num1 = num1->next;
        }
        else if (num1->num > num2->num)
        {
            // Создание нового узла с множителем и степенью из num2
            tmp = node_create(num2->num, num2->pow);
            num2 = num2->next;
        }
        else
        {
            // Сложение степеней одинаковых множителей
            tmp = node_create(num1->num, num1->pow + num2->pow);
            num1 = num1->next;
            num2 = num2->next;
        }

        // Проверка успешности создания нового узла
        if (!tmp)
        {
            list_free(res);
            return NULL;
        }

        // Добавление нового узла в результирующий список
        res = list_add_tail(res, tmp);
    }

    // Обработка оставшихся узлов в num1
    while (num1)
    {
        tmp = node_create(num1->num, num1->pow);
        if (!tmp)
        {
            list_free(res);
            return NULL;
        }
        res = list_add_tail(res, tmp);
        num1 = num1->next;
    }

    // Обработка оставшихся узлов в num2
    while (num2)
    {
        tmp = node_create(num2->num, num2->pow);
        if (!tmp)
        {
            list_free(res);
            return NULL;
        }
        res = list_add_tail(res, tmp);
        num2 = num2->next;
    }

    // Возвращение результирующего списка
    return res;
}

node_t *sqr_num(node_t *num)
{
    node_t *res = NULL;
    node_t *tmp = NULL;

    while (num)
    {
        tmp = node_create(num->num, num->pow + num->pow);
        if (!tmp)
        {
            list_free(res);
            return NULL;
        }
        res = list_add_tail(res, tmp);
        num = num->next;
    }
    return res;
}

int reduce_nums(node_t *num1, node_t *num2, node_t **new_num1, node_t **new_num2)
{
    node_t *reduced_num1 = NULL, *reduced_num2 = NULL, *tmp;

    while (num1 && num2)
    {
        if (num1->num < num2->num)
        {
            tmp = node_create(num1->num, num1->pow);
            if (!tmp)
            {
                list_free(reduced_num1);
                list_free(reduced_num2);
                return ERR_NULL;
            }
            reduced_num1 = list_add_tail(reduced_num1, tmp);
            num1 = num1->next;
        }
        else if (num1->num > num2->num)
        {
            tmp = node_create(num2->num, num2->pow);
            if (!tmp)
            {
                list_free(reduced_num1);
                list_free(reduced_num2);
                return ERR_NULL;
            }
            reduced_num2 = list_add_tail(reduced_num2, tmp);
            num2 = num2->next;
        }
        else
        {
            if (num1->pow > num2->pow)
            {
                tmp = node_create(num1->num, num1->pow - num2->pow);
                if (!tmp)
                {
                    list_free(reduced_num1);
                    list_free(reduced_num2);
                    return ERR_NULL;
                }
                reduced_num1 = list_add_tail(reduced_num1, tmp);
            }
            else if (num1->pow < num2->pow)
            {
                tmp = node_create(num2->num, num2->pow - num1->pow);
                if (!tmp)
                {
                    list_free(reduced_num1);
                    list_free(reduced_num2);
                    return ERR_NULL;
                }
                reduced_num2 = list_add_tail(reduced_num2, tmp);
            }
            num1 = num1->next;
            num2 = num2->next;
        }
    }

    while (num1)
    {
        tmp = node_create(num1->num, num1->pow);
        if (!tmp)
        {
            list_free(reduced_num1);
            list_free(reduced_num2);
            return ERR_NULL;
        }
        reduced_num1 = list_add_tail(reduced_num1, tmp);
        num1 = num1->next;
    }
    while (num2)
    {
        tmp = node_create(num2->num, num2->pow);
        if (!tmp)
        {
            list_free(reduced_num1);
            list_free(reduced_num2);
            return ERR_NULL;
        }
        reduced_num2 = list_add_tail(reduced_num2, tmp);
        num2 = num2->next;
    }

    *new_num1 = reduced_num1;
    *new_num2 = reduced_num2;
    return OK;
}

node_t *div_nums(node_t *num1, node_t *num2)
{
    if (!num2 || !num1)
        return NULL;

    node_t *res = NULL, *reduced_num1 = NULL, *reduced_num2 = NULL;

    int rc = reduce_nums(num1, num2, &reduced_num1, &reduced_num2);
    if (rc)
        return NULL;

    if (reduced_num2 == NULL)
        return reduced_num1;

    int new_num1 = get_num_from_list(reduced_num1);
    int new_num2 = get_num_from_list(reduced_num2);
    list_free(reduced_num1);
    list_free(reduced_num2);

    int num = new_num1 / new_num2;
    rc = init_list_from_num(&res, num);
    
    if (rc)
        return NULL;
    return res;
}
