#ifndef LIST_H
#define LIST_H

#include "node_list.h"
#include <stdbool.h>

// Двусвязный список
typedef struct
{
    node_t *head;
    node_t *tail;
} list_t;

/**
 * \brief Инициализирует новый список.
 *
 * Выделяет память под новый список и инициализирует его. Возвращает указатель на
 * новый список.
 *
 * \return Указатель на новый список или NULL в случае ошибки выделения памяти.
 */
list_t *list_init(void);

/**
 * \brief Добавляет новый узел с данными в конец списка.
 *
 * Добавляет новый узел с данными в конец списка. Если список пуст, новый узел становится
 * единственным элементом в списке.
 *
 * \param list [in, out] - Указатель на структуру списка.
 * \param data [in] - Указатель на данные, которые будут добавлены в узел.
 * \return Указатель на обновленный список или NULL в случае ошибки.
 */
list_t *list_add_tail(list_t *list, const void *data);

/**
 * \brief Удаляет узлы с данными из списка.
 *
 * Удаляет все узлы с данными, совпадающими с указанными, из списка. Если узел с данными
 * не найден, список остается неизменным.
 *
 * \param list [in, out] - Указатель на структуру списка.
 * \param data [in] - Указатель на данные, которые нужно удалить из списка.
 * \param comparator [in] - Функция для сравнения данных в узлах списка.
 * \param free_data [in] - Функция для освобождения памяти, занимаемой данными в узлах списка.
 * \return Указатель на обновленный список или NULL в случае ошибки.
 */
list_t *list_remove(list_t *list, const void *data, int (*comparator)(const void*, const void*), void (*free_data)(void*));

/**
 * \brief Находит узел с данными в списке.
 *
 * Находит первый узел с данными, совпадающими с указанными, в списке.
 *
 * \param list [in] - Указатель на структуру списка.
 * \param data [in] - Указатель на данные, которые нужно найти в списке.
 * \param comparator [in] - Функция для сравнения данных в узлах списка.
 * \return Указатель на найденный узел или NULL, если узел с данными не найден.
 */
node_t *list_find(list_t *list, const void *data, int (*comparator)(const void*, const void*));

/**
 * \brief Находит узел с минимальным значением данных в списке.
 *
 * Перебирает все узлы в списке, сравнивает данные с использованием указанной функции-компаратора
 * и возвращает указатель на узел с минимальным значением данных.
 *
 * \param list Указатель на список.
 * \param comparator Указатель на функцию-компаратор для сравнения данных в узлах.
 * \return Указатель на узел с минимальным значением данных или NULL, если список пуст.
 */
node_t *list_find_min(list_t *list, int (*comparator)(const void*, const void*));

/**
 * \brief Находит узел с максимальным значением данных в списке.
 *
 * Перебирает все узлы в списке, сравнивает данные с использованием указанной функции-компаратора
 * и возвращает указатель на узел с максимальным значением данных.
 *
 * \param list Указатель на список.
 * \param comparator Указатель на функцию-компаратор для сравнения данных в узлах.
 * \return Указатель на узел с максимальным значением данных или NULL, если список пуст.
 */
node_t *list_find_max(list_t *list, int (*comparator)(const void*, const void*));

/**
 * \brief Проверяет, пуст ли список.
 *
 * \param list [in] - Указатель на структуру списка.
 * \return true, если список пуст, иначе false.
 */
bool list_is_empt(list_t *list);

/**
 * \brief Выводит содержимое списка в файл.
 *
 * Выводит содержимое списка в указанный файл, используя указанную функцию для
 * печати каждого узла.
 *
 * \param f [in, out] - Указатель на файл, куда будет производиться вывод.
 * \param list [in] - Указатель на структуру списка.
 * \param print [in] - Указатель на функцию для печати содержимого узла.
 */
void list_print(FILE *f, list_t *list, void (*print)(FILE*, const void*));

/**
 * \brief Очищает список, освобождая память, занятую данными в узлах.
 *
 * Освобождает память, занятую данными в узлах списка, и устанавливает указатели
 * head и tail в NULL.
 *
 * \param list Указатель на список.
 * \param free_data Указатель на функцию для освобождения памяти, занятой данными
 * в узлах. Может быть NULL, если не требуется освобождение памяти.
 */
void list_make_empt(list_t *list, void (*free_data)(void*));

/**
 * \brief Освобождает память, занимаемую списком.
 *
 * Освобождает память, занимаемую списком, включая каждый узел. Также освобождает
 * память, занимаемую данными в каждом узле с использованием указанной функции.
 *
 * \param list [in] - Указатель на структуру списка.
 * \param free_data [in] - Указатель на функцию для освобождения памяти данных в узле.
 */
void list_free(list_t *list, void (*free_data)(void*));

#endif
