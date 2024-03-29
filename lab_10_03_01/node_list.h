#ifndef NODE_LIST_H
#define NODE_LIST_H

#include <stdio.h>

/// Узел двусвязного списка
typedef struct node_t
{
    void *data;
    struct node_t *prev;
    struct node_t *next;
} node_t;

/**
 * \brief Создание нового узла списка.
 *
 * Функция выделяет память и создает новый узел списка с указанными данными.
 *
 * \param data [in] - Указатель на данные, которые будут храниться в узле.
 * \return Указатель на новый узел списка или NULL в случае ошибки выделения памяти.
 */
node_t *node_create(void *data);

/**
 * \brief Освобождение памяти, занятой узлом списка.
 *
 * Функция освобождает память, выделенную под узел списка.
 *
 * \param node [in] - Указатель на узел списка, который нужно освободить.
 * \param free_data [in] - В случае если необходимо освободить память выделенную под data, передается указатель на функцуию освобождения, иначе NULL
 */
void node_free(node_t *node, void (*free_data)(void*));

/**
 * \brief Печать содержимого узла списка.
 *
 * Функция печатает содержимое узла списка, используя указанную функцию печати.
 *
 * \param f [in\out] - Указатель на файл, в который будет произведена печать.
 * \param node [in] - Указатель на узел списка, содержимое которого нужно напечатать.
 * \param print [in] - Указатель на функцию печати содержимого узла.
 */
void node_print(FILE *f, const node_t *node, void (*print)(FILE*, const void*));

#endif
