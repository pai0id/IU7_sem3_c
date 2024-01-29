#ifndef __LIB_ARR_H
#define __LIB_ARR_H

#include <stdlib.h>
#include "liberr.h"

/**
 * \brief Заполняет массив простыми числами.
 *
 * Заполняет переданный массив указанного размера простыми числами.
 *
 * \param arr [out] Указатель на массив, который будет заполнен простыми числами.
 * \param size [in] Размер массива.
 */
void fill_primes(int *arr, size_t size);

/**
 * \brief Копирует элементы из исходного массива и добавляет число для четных элементов.
 *
 * Копирует элементы из исходного массива в целевой массив, а для каждого четного элемента
 * добавляет заданное число.
 *
 * \param src [in] Указатель на исходный массив.
 * \param src_size [in] Размер исходного массива.
 * \param dst [out] Указатель на целевой массив, в который будут скопированы элементы.
 * \param dst_available_size [in] Доступное пространство в целевом массиве.
 * \param dst_size [out] Количество элементов, записанных в целевой массив.
 * \param num [in] Число, которое добавляется для каждого четного элемента.
 * 
 * \return Код ошибки:
 *         - LIB_OK, если элементы успешно скопированы
 *         - LIB_ERR_SIZE, если размер недостаточен
 */
int ncpy_and_add(int *src, size_t src_size, int *dst, size_t dst_available_size, size_t *dst_size, int num);

#endif