/*!
    \file
    \brief Заголовочный файл с описанием структуры и модулями для работы с ними
*/

#ifndef FILM_H
#define FILM_H

#include <stdio.h>
#include "err.h"

#define TITLE_LEN 25    /// Максимальная длина названия
#define NAME_LEN 25     /// Максимальная длина фамилии режиссера
#define TITLE "title"
#define NAME "name"
#define YEAR "year"

struct film_t
{
    char title[TITLE_LEN + 1];  /// Название фильма (<= 25 симв.)
    char name[NAME_LEN + 1];    /// Фамилия режисера (<= 25 симв.)
    int year;                   /// Год выхода
};

typedef int (*cmp_t)(const struct film_t *lp, const struct film_t *rp);

/**
 * \brief Считывает строку из файла.
 *
 * \param f [in] - указатель на файл, из которого будет считана строка
 * \param str [out] - указатель на буфер, в который будет сохранена считанная строка
 * \param size [in] - максимальная длина считываемой строки (включая символ '\0')
 * \param max_size [in] - максимально допустимая длина строки (без символа '\0')
 * 
 * \return Код ошибки:
 *         - OK, если ошибок не возникло
 *         - ERR_IO, если произошла ошибка ввода-вывода
 *         - ERR_RANGE, если длина строки не соответствует ожидаемой
 */
int str_read(FILE *f, char *str, size_t size, size_t max_size);

/**
 * \brief Считывает информацию о фильме из файла и сохраняет её в структуру.
 *
 * \param f [in] - указатель на файл, из которого будет считана информация о фильме
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
 * \param f [in] - указатель на файл, в который будет выведена информация о фильме
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
