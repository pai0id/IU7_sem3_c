/*!
    \file
    \brief Заголовочный файл с описанием структуры и модулями для работы с ними
*/

#ifndef FILM_H
#define FILM_H

#define _GNU_SOURCE

#include <stdlib.h>
#include <stddef.h>
#include "err.h"
#include <stdio.h>

#define TITLE "title"
#define NAME "name"
#define YEAR "year"

struct film_t
{
    char *title;   /// Название фильмa
    char *name;    /// Фамилия режисера
    int year;      /// Год выхода
};

typedef int (*cmp_t)(const struct film_t *lp, const struct film_t *rp);

/**
 * \brief Инициализация содержимого структуры film_t.
 *
 * Функция инициализирует поля структуры film_t с заданными значениями.
 *
 * \param fp [in, out] - указатель на структуру film_t
 * \param title [in] - указатель на строку с названием фильма
 * \param name [in] - указатель на строку с именем режиссера
 * \param year [in] - год выпуска фильма
 */
void film_init_content(struct film_t *fp, char *title, char *name, int year);

/**
 * \brief Освобождение памяти, выделенной под содержимое структуры film_t.
 *
 * Функция освобождает память, выделенную под поля title и name структуры film_t,
 * и устанавливает указатели на нулевые значения.
 *
 * \param fp [in, out] - указатель на структуру film_t
 */
void film_free_content(struct film_t *fp);

/**
 * \brief Считывает информацию о фильме из файла и сохраняет её в структуру.
 *
 * \param f [in/out] - указатель на файл, из которого будет считана информация о фильме
 * \param fp [out] - указатель на структуру film_t, в которую будет сохранена информация о фильме
 * 
 * \return Код ошибки:
 *         - OK, если ошибок не возникло
 *         - ERR_IO, если произошла ошибка ввода-вывода
 *         - ERR_RANGE, если длина строки не соответствует ожидаемой или значение года некорректное
 */
int film_read(FILE *f, struct film_t *fp);

/**
 * \brief Выводит информацию о фильме в указанный файл.
 *
 * Эта функция выводит информацию о фильме, хранящуюся в структуре film_t, в указанный файл.
 *
 * \param f [in/out] - указатель на файл, в который будет выведена информация о фильме
 * \param fp [in] - указатель на структуру film_t, содержащую информацию о фильме
 */
void film_print(FILE *f, const struct film_t *fp);

/**
 * \brief Сравнивает два фильма по заголовкам (названиям).
 *
 * \param lp [in] - указатель на первый фильм для сравнения
 * \param rp [in] - указатель на второй фильм для сравнения
 * 
 * \return Результат сравнения:
 *         - отрицательное число, если заголовок первого фильма меньше заголовка второго
 *         - положительное число, если заголовок первого фильма больше заголовка второго
 *         - 0, если заголовки фильмов идентичны
 */
int film_cmp_by_title(const struct film_t *lp, const struct film_t *rp);

/**
 * \brief Сравнивает два фильма по фамилиям режисера.
 *
 * \param lp [in] - указатель на первый фильм для сравнения
 * \param rp [in] - указатель на второй фильм для сравнения
 * 
 * \return Результат сравнения:
 *         - отрицательное число, если фамилия режиссера первого фильма меньше второго
 *         - положительное число, если фамилия режиссера первого фильма больше второго
 *         - 0, если фамилии режисеров фильмов идентичны
 */
int film_cmp_by_name(const struct film_t *lp, const struct film_t *rp);

/**
 * \brief Сравнивает два фильма по году выпуска.
 *
 * \param lp [in] - указатель на первый фильм для сравнения
 * \param rp [in] - указатель на второй фильм для сравнения
 * 
 * \return Результат сравнения:
 *         - положительное число, если год выпуска первого фильма больше года выпуска второго
 *         - отрицательное число, если год выпуска первого фильма меньше года выпуска второго
 *         - 0, если годы выпуска фильмов идентичны
 */
int film_cmp_by_year(const struct film_t *lp, const struct film_t *rp);

#endif
