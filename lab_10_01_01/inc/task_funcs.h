/*!
    \file
    \brief Заголовочный файл c функциями, необходимыми для моей задачи
*/

#ifndef TASK_FUNCS_H
#define TASK_FUNCS_H

#include "list.h"
#include "film_arr.h"

/**
 * \brief Инициализация списка из массива фильмов.
 *
 * Функция создает список из массива фильмов.
 *
 * \param head [out] - Указатель на указатель на голову списка.
 * \param film_arr [in] - Массив структур film_t.
 * \param n_films [in] - Количество фильмов в массиве.
 * \return Код ошибки (OK, ERR_MEM).
 */
int init_list_from_film_arr(node_t **head, struct film_t *film_arr, size_t n_films);

#endif
