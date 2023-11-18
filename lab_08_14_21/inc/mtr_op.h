#ifndef MTR_OP_H
#define MTR_OP_H

#include <stddef.h>
#include "err.h"

/**
 * \brief Умножение двух матриц.
 *
 * Функция умножает матрицу a размером a_n x a_m на матрицу b размером b_n x b_m,
 * и возвращает результат в матрице c размером c_n x c_m.
 *
 * \param a [in] - указатель на массив указателей на строки матрицы a
 * \param a_n [in] - количество строк в матрице a
 * \param a_m [in] - количество столбцов в матрице a
 * \param b [in] - указатель на массив указателей на строки матрицы b
 * \param b_n [in] - количество строк в матрице b
 * \param b_m [in] - количество столбцов в матрице b
 * \param c [out] - указатель на массив указателей на строки результирующей матрицы c (возвращается функцией)
 * \param c_n [out] - количество строк в результирующей матрице (возвращается функцией)
 * \param c_m [out] - количество столбцов в результирующей матрице (возвращается функцией)
 *
 * \return Код ошибки:
 *         - OK, если ошибок не возникло
 *         - ERR_RANGE, если размеры матриц не позволяют выполнить умножение
 *         - ERR_MEM, если не удалось выделить память под результирующую матрицу
 */
int matrix_mult(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m);

/**
 * \brief Сложение двух матриц.
 *
 * Функция складывает матрицу a размером a_n x a_m с матрицей b размером b_n x b_m,
 * и возвращает результат в матрице c размером c_n x c_m.
 *
 * \param a [in] - указатель на массив указателей на строки матрицы a
 * \param a_n [in] - количество строк в матрице a
 * \param a_m [in] - количество столбцов в матрице a
 * \param b [in] - указатель на массив указателей на строки матрицы b
 * \param b_n [in] - количество строк в матрице b
 * \param b_m [in] - количество столбцов в матрице b
 * \param c [out] - указатель на массив указателей на строки результирующей матрицы c (возвращается функцией)
 * \param c_n [out] - количество строк в результирующей матрице (возвращается функцией)
 * \param c_m [out] - количество столбцов в результирующей матрице (возвращается функцией)
 *
 * \return Код ошибки:
 *         - OK, если ошибок не возникло
 *         - ERR_RANGE, если размеры матриц не позволяют выполнить сложение
 *         - ERR_MEM, если не удалось выделить память под результирующую матрицу
 */
int matrix_add(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m);

/**
 * \brief Решение системы линейных уравнений методом Гаусса.
 *
 * Функция решает систему линейных уравнений Ax = f, где A - квадратная матрица, f - вектор.
 * Результат записывается в вектор f.
 *
 * \param mtr [in/out] - указатель на двумерный массив, представляющий собой квадратную матрицу системы
 * \param n [in] - размерность системы (количество уравнений и неизвестных)
 * \param f [in/out] - указатель на вектор значений правых частей уравнений (возвращается решением системы)
 *
 * \return Код ошибки:
 *         - OK, если ошибок не возникло
 *         - ERR_UNSOLVABE, если система уравнений не имеет решений
 */
int solve_eq(double **mtr, size_t n, double *f);

/**
 * \brief Транспонирование матрицы.
 *
 * Функция транспонирует квадратную матрицу mtr размерности n x n.
 *
 * \param mtr [in/out] - указатель на квадратную матрицу
 * \param n [in] - размерность матрицы
 */
void matrix_transpose(double **mtr, size_t n);

/**
 * \brief Расчет обратной матрицы.
 *
 * Функция вычисляет обратную матрицу для квадратной матрицы mtr размерности mtr_n x mtr_m.
 *
 * \param mtr [in] - указатель на квадратную матрицу
 * \param mtr_n [in] - количество строк в матрице
 * \param mtr_m [in] - количество столбцов в матрице
 * \param res [out] - указатель на обратную матрицу
 * \param res_n [out] - количество строк в обратной матрице
 * \param res_m [out] - количество столбцов в обратной матрице
 *
 * \return Код ошибки:
 *         - OK - успешное выполнение
 *         - ERR_RANGE - неквадратная матрица
 *         - ERR_MEM - ошибка выделения памяти
 *         - ERR_UNSOLVABLE - матрица вырожденная
 */
int matrix_calc_rev(double **mtr, size_t mtr_n, size_t mtr_m, double ***res, size_t *res_n, size_t *res_m);

#endif
