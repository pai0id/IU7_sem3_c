#ifndef LIST_H
#define LIST_H

#include "node_list.h"

/**
 * \brief Добавление узла в конец списка.
 *
 * Функция добавляет узел в конец списка.
 *
 * \param head [in] - Указатель на голову списка.
 * \param pnode [in] - Указатель на узел, который нужно добавить в конец списка.
 * \return Указатель на новую голову списка.
 */
node_t *list_add_tail(node_t *head, node_t *pnode);

/**
 * \brief Печать списка в файл.
 *
 * Функция выводит содержимое списка в файл с использованием функции print.
 *
 * \param f [in\out] - Указатель на файл.
 * \param head [in] - Указатель на голову списка.
 * \param print [in] - Функция печати элемента списка.
 */
void list_print(FILE *f, node_t *head, void (*print)(FILE*, const void*));

/**
 * \brief Освобождение памяти, занятой списком.
 *
 * Функция освобождает память, занятую списком, начиная с головы.
 *
 * \param head [in] - Указатель на голову списка.
 */
void list_free(node_t *head);

/**
 * \brief Поиск узла в списке по значению.
 *
 * Функция выполняет поиск узла в списке с использованием заданной функции-компаратора.
 *
 * \param head [in] - Указатель на голову списка.
 * \param data [in] - Указатель на данные, которые необходимо найти.
 * \param comparator [in] - Функция-компаратор для сравнения данных.
 *
 * \return Указатель на найденный узел или NULL, если узел не найден.
 */
node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*));

/**
 * \brief Вставка узла в список перед указанным узлом.
 *
 * Функция выполняет вставку узла в список перед указанным узлом.
 *
 * \param head [in/out] - Указатель на указатель на голову списка.
 * \param elem [in] - Указатель на вставляемый узел.
 * \param before [in] - Указатель на узел, перед которым производится вставка.
 */
void insert(node_t **head, node_t *elem, node_t *before);

/**
 * \brief Удаление дубликатов из списка.
 *
 * Функция удаляет дубликаты из связанного списка с использованием
 * заданного компаратора для сравнения узлов.
 *
 * \param head [in/out] - Указатель на указатель на голову списка.
 * \param comparator [in] - Функция сравнения узлов.
 */
void remove_duplicates(node_t **head, int (*comparator)(const void*, const void*));

/**
 * \brief Разделение списка на две части.
 *
 * Функция разделяет переданный список на две части: одну, содержащую первую
 * половину элементов, и другую, содержащую вторую половину элементов.
 *
 * \param head [in] - Указатель на голову исходного списка.
 * \param back [out] - Указатель на указатель на голову второй половины списка.
 */
void front_back_split(node_t *head, node_t **back);

/**
 * \brief Объединение двух отсортированных списков в один.
 *
 * Функция объединяет два отсортированных списка в один отсортированный список.
 *
 * \param head_a [in/out] - Указатель на указатель на голову первого списка.
 * \param head_b [in/out] - Указатель на указатель на голову второго списка.
 * \param comparator [in] - Указатель на функцию сравнения элементов.
 * \return Указатель на голову объединенного списка.
 */
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void*, const void*));

/**
 * \brief Сортировка списка с использованием сортировки слиянием.
 *
 * Функция сортирует список с использованием алгоритма сортировки слиянием.
 *
 * \param head [in/out] - Указатель на указатель на голову списка.
 * \param comparator [in] - Указатель на функцию сравнения элементов.
 * 
 * \return "Новая" голова списка
 */
node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif
