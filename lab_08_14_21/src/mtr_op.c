#include "mtr_op.h"
#include "mtr_alloc.h"
#include "mtr_io.h"
#include <stdlib.h>
#include <math.h>

int matrix_mult(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m)
{
    if (a_m != b_n)
        return ERR_RANGE;

    *c_n = a_n;
    *c_m = b_m;
    *c = matrix_allocate(*c_n, *c_m);
    if (*c == NULL)
        return ERR_MEM;

    for (size_t i = 0; i < a_n; ++i)
    {
        for (size_t j = 0; j < b_m; ++j)
        {
            (*c)[i][j] = 0;
            for (size_t k = 0; k < a_m; ++k)
                (*c)[i][j] += a[i][k] * b[k][j];
        }
    }
    return OK;
}

int matrix_add(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m)
{
    if (a_n != b_n || a_m != b_m)
        return ERR_RANGE;

    *c_n = a_n;
    *c_m = a_m;
    *c = matrix_allocate(*c_n, *c_m);
    if (*c == NULL)
        return ERR_MEM;

    for (size_t i = 0; i < a_n; ++i)
        for (size_t j = 0; j < a_m; ++j)
            (*c)[i][j] = a[i][j] + b[i][j];
    return OK;
}

int solve_eq(double **mtr, size_t n, double *f)
{
    double divisor, factor, *tmp, tmp_el;

    // Начинаю итерацию по каждой строке матрицы
    for (size_t i = 0; i < n; ++i)
    {
        // Запоминаю значение диагонального элемента текущей строки
        divisor = mtr[i][i];
        // Проверяю, не равен ли диагональный элемент нулю
        if (fabs(divisor) < EPS)
        {
            int found = 0;
            // Если диагональный элемент нулевой, ищу другую строку с ненулевым элементом
            for (size_t k = i + 1; k < n; ++k)
            {
                if (fabs(mtr[k][i]) >= EPS)
                {
                    // Меняю строки местами в матрице и в векторе правой части
                    tmp = mtr[k];
                    mtr[k] = mtr[i];
                    mtr[i] = tmp;
                    tmp_el = f[k];
                    f[k] = f[i];
                    f[i] = tmp_el;
                    found = 1;
                    break;
                }
            }
            // Если не найдено ненулевого элемента, сообщаю, что система нерешима
            if (!found)
                return ERR_UNSOLVABLE;
            else
                divisor = mtr[i][i];
        }
        // Делю элементы строки и соответствующий элемент вектора правой части на диагональный элемент
        f[i] /= divisor;
        for (size_t j = 0; j < n; ++j)
            mtr[i][j] /= divisor;
        // Привожу остальные строки к ступенчатому виду
        for (size_t k = 0; k < n; ++k)
        {
            if (k != i)
            {
                factor = mtr[k][i];
                f[k] -= factor * f[i];
                for (size_t j = 0; j < n; ++j)
                    mtr[k][j] -= factor * mtr[i][j];
            }
        }
    }
    return OK;
}

void matrix_transpose(double **mtr, size_t n)
{
    double tmp;

    // Итерируюсь по верхнему треугольнику матрицы
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            // Обмениваю значения элементов относительно главной диагонали
            tmp = mtr[i][j];
            mtr[i][j] = mtr[j][i];
            mtr[j][i] = tmp;
        }
    }
}

int matrix_calc_rev(double **mtr, size_t mtr_n, size_t mtr_m, double ***res, size_t *res_n, size_t *res_m)
{
    double **tmp_mtr;
    int rc = OK;

    // Проверка, что матрица квадратная
    if (mtr_n != mtr_m)
        return ERR_RANGE;

    // Устанавливаю размеры результирующей матрицы
    *res_n = mtr_n;
    *res_m = mtr_m;

    // Выделяю память под результирующую матрицу и заполняю ее единичной матрицей
    *res = matrix_allocate(*res_n, *res_m);
    if (*res == NULL)
        return ERR_MEM;
    matrix_fill_d_ones(*res, *res_n, *res_m);

    // Выделяю временную матрицу
    tmp_mtr = matrix_allocate(mtr_n, mtr_m);
    if (tmp_mtr == NULL)
    {
        matrix_free(*res, *res_n);
        return ERR_MEM;
    }

    // Итерация по столбцам
    for (size_t i = 0; i < *res_m && rc == OK; ++i)
    {
        // Копирую исходную матрицу во временную
        matrix_copy(mtr, mtr_n, mtr_m, tmp_mtr);

        // Решаю систему уравнений для получения i-го столбца обратной матрицы
        rc = solve_eq(tmp_mtr, mtr_n, (*res)[i]);
    }

    // Освобождаю память, выделенную под временную матрицу
    matrix_free(tmp_mtr, mtr_n);

    // Транспонирую результирующую матрицу
    matrix_transpose(*res, *res_n);

    // Если система уравнений несовместна, освобождаю память и возвращаю ошибку
    if (rc == ERR_UNSOLVABLE)
        matrix_free(*res, *res_n);

    return rc;
}
